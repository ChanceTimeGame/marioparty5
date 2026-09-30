/*
 * m559dll -- a Bowser minigame (MG_TYPE_KUPA, overlay #70). Two waves of
 * objects fall on a round arena (100 at main frame 5, 48 at frame 200) while
 * the players walk clear; one landing within 55 of a player takes that player
 * out. Everyone still standing when the round ends (frame 330) gets 10 coins.
 *
 * COMPLETE: every function written from the reference assembly (see NOTES.md
 * for the per-function record). Line ranges are into
 * build/mp5-asm/m559dll/asm/REL/m559dll/m559.s.
 *
 * Shape: seqman (MgSeqCreatePrio, lbl_1_data_108) + own OMOBJ groups, one TU,
 * built from the same parts as m560dll (also KUPA):
 *
 *  - fn_1_56D0..fn_1_65B4 are the shared helper block. They are
 *    instruction-identical to m563's util.o copy (and to m560.c's
 *    M560IdListInit..M560VolGetEx), so this file #includes
 *    "REL/m563dll/math.c" first. Already written; not W2 work.
 *  - fn_1_69D8..fn_1_7E88 are m560.c's billboard library, instruction-identical
 *    (symbol-normalized) to M560MtxTranspose..M560BillCreateEx, except that
 *    fn_1_7E88 sets model layer 4 where M560BillCreateEx sets 5. Port those
 *    bodies from m560.c (the types below are m560's, renamed).
 *  - fn_1_6678 is this overlay's own M559BILLFUNC (m560's is 310 insns).
 *
 * Emission order: CodeWarrior emits this file's own functions first, then
 * those of its #included files in include order. Defining the billboard
 * statics in this file put them ahead of math.c's; including them from
 * bill.c after math.c gives the reference order. Keep both includes.
 *
 * _prolog and _epilog are not reproduced.
 */

#include "game/hu3d.h"
#include "game/sprite.h"
#include "dolphin/mtx.h"
#include "humath.h"
#include "string.h"

/* m560dll's billboard system, renamed (see m560.c for the field notes). */
typedef struct M559Bill_s M559_BILL;
typedef void (*M559BILLFUNC)(HU3DMODEL *modelP, M559_BILL *work, Mtx mtx);

typedef struct M559BillPart_s {
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
} M559_BILLPART;

struct M559Bill_s {
    /* 0x00 */ M559BILLFUNC func;
    /* 0x04 */ ANIMDATA *anim;
    /* 0x08 */ HuVecF *posSrc;
    /* 0x0C */ float *angleSrc;
    /* 0x10 */ M559_BILLPART *part;
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

static void fn_1_6678(HU3DMODEL *modelP, M559_BILL *work, Mtx mtx);
static void fn_1_69D8(Mtx src, Mtx dst);
static void fn_1_6A54(HuVecF *src, HuVecF *dst, float scale, s16 count);
static void fn_1_6AB0(HuVec2f *st, HuVec2f *cellTbl, s16 cell, float width, float height);
static void fn_1_6B54(HU3DMODEL *modelP, Mtx *mtx);
static void fn_1_729C(HuVec2f *st, s16 count, s16 cellX, float w, float h);
static HU3DMODELID fn_1_7368(ANIMDATA *anim, HuVecF *posSrc, float *angleSrc, s16 maxCnt, float size, s16 cellW, s16 cellH);
static M559_BILLPART *fn_1_79C0(HU3DMODELID modelId, HuVecF *pos, GXColor *color, float scale, float zRot);
static void fn_1_7AC8(HU3DMODELID modelId, M559BILLFUNC func);
static void fn_1_7B00(HU3DMODELID modelId, u8 value);
static void fn_1_7B30(HU3DMODELID modelId);
static BOOL fn_1_7B6C(HU3DMODELID modelId);
static void fn_1_7C28(HU3DMODELID modelId, s16 count, HuVecF *pos, float angle, float timeMax, float posYTarget);
static HU3DMODELID fn_1_7E88(HuVecF *posSrc, float *angleSrc, s16 maxCnt);

#include "REL/m563dll/math.c"
#include "REL/m559dll/bill.c"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/memory.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/hsfformat.h"
#include "game/mg/seqman.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/sprite.h"

#include "datadir_enum.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

/* 0x8C bytes per player (group 0, fn_1_694). */
typedef struct M559Player_s {
    /* 0x00 */ s16 motNo;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ HU3DMODELID mdlId;
    /* 0x14 */ s32 no;
    /* 0x18 */ s32 charNo;
    /* 0x1C */ s32 padNo;
    /* 0x20 */ s32 mode;
    /* 0x24 */ s32 timer;
    /* 0x28 */ HuVecF pos;
    /* 0x34 */ HuVecF posOld;
    /* 0x40 */ HuVecF rot;
    /* 0x4C */ float speed;
    /* 0x50 */ HuVecF vel;
    /* 0x5C */ float unk5C;
    /* 0x60 */ float stkX;
    /* 0x64 */ float stkY;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 dif;
    /* 0x70 */ s32 comMode;
    /* 0x74 */ HuVecF target;
    /* 0x80 */ s32 comTimer;
    /* 0x84 */ s32 comWait;
    /* 0x88 */ s32 comWaitMax;
} M559_PLAYER;

/* 0x2C bytes: Bowser (group 1, fn_1_3068). */
typedef struct M559Kupa_s {
    /* 0x00 */ HU3DMODELID mdlId;
    /* 0x02 */ s16 pad2;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ s32 motNo;
    /* 0x20 */ s32 mode;
    /* 0x24 */ s32 timer;
    /* 0x28 */ s32 billMdlId;
} M559_KUPA;

/* 0x58 bytes: one falling object (fn_1_41D4 / fn_1_4910 create them). */
typedef struct M559Item_s {
    /* 0x00 */ HU3DMODELID mdlId;
    /* 0x02 */ HU3DMODELID shadowMdlId;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF startPos;
    /* 0x1C */ HuVecF rot;
    /* 0x28 */ HuVecF scale;
    /* 0x34 */ float unk34;
    /* 0x38 */ float fallSpeed;
    /* 0x3C */ float unk3C;
    /* 0x40 */ s32 mode;
    /* 0x44 */ s32 timer;
    /* 0x48 */ s32 delay;
    /* 0x4C */ s32 fallTime;
    /* 0x50 */ float unk50;
    /* 0x54 */ float unk54;
} M559_ITEM;

void ObjectSetup(void);
void fn_1_694(OMOBJ *obj);
void fn_1_A5C(OMOBJ *obj);
void fn_1_F48(OMOBJ *obj);
void fn_1_1070(OMOBJ *obj);
s32 fn_1_1210(HuVecF *out);
s32 fn_1_1394(HuVecF *pos, HuVecF *out, float radius);
s32 fn_1_1668(HuVecF *pos, HuVecF *out, float radius);
s32 fn_1_1894(OMOBJ *obj);
s32 fn_1_19D8(OMOBJ *obj);
void fn_1_1B1C(M559_PLAYER *player, OMOBJ *obj);
void fn_1_1F28(M559_PLAYER *player);
void fn_1_20D8(s16 mode, s16 frameNo);
void fn_1_23C8(s16 mode, s16 frameNo);
void fn_1_25F8(s16 mode, s16 frameNo);
void fn_1_265C(s16 mode, s16 frameNo);
void fn_1_2714(s16 mode, s16 frameNo);
void fn_1_27A0(s16 mode, s16 frameNo);
void fn_1_2948(OMOBJ *obj, s32 motNo, float shift, u32 attr);
void fn_1_29D4(void);
void fn_1_29D8(OMOBJ *obj);
void fn_1_2CA8(void);
void fn_1_3068(OMOBJ *obj);
void fn_1_32D0(OMOBJ *obj);
void fn_1_3854(OMOBJ *obj, s32 motNo, float shift, u32 attr);
s32 fn_1_3918(s32 side, float x, float z);
void fn_1_3A1C(void);
void fn_1_3DA8(void);
void fn_1_40A4(void);
void fn_1_413C(void);
void fn_1_41D4(float x, float y, float z);
void fn_1_4364(OMOBJ *obj);
void fn_1_4504(OMOBJ *obj);
void fn_1_4848(OMOBJ *obj);
void fn_1_4910(float x, float y, float z);
void fn_1_4A9C(OMOBJ *obj);
void fn_1_4C3C(OMOBJ *obj);
void fn_1_4F70(OMOBJ *obj);
void fn_1_5038(OMOBJ *obj);
float fn_1_5308(s32 from, s32 to, s32 time);
BOOL fn_1_542C(void);
void fn_1_54C4(void);
void fn_1_5514(void);
void fn_1_5564(void);
void fn_1_5578(void);
void fn_1_55A8(void);
s16 fn_1_55D8(HuVecF *pos);
s16 fn_1_5654(HuVecF *pos);

/*
 * .rodata:0x7C { 255, 255, 255, 255 } is a GXColor local in fn_1_32D0 and
 * fn_1_7C28; write it as a local. The .data strings are literals.
 */

/* --- .data --- */

HuVecF lbl_1_data_0 = { 0.0f, 10000.0f, 10000.0f };   /* light position */
HuVecF lbl_1_data_C = { 0.0f, 0.0f, 0.0f };           /* light target */
GXColor lbl_1_data_18 = { 255, 255, 255, 255 };

/* Character motions. */
u32 lbl_1_data_1C[8] = { 0x008C0091, 0x008C0000, 0x008C0086, 0x008C0031, 0x008C0001, 0x008C002C, 0x008C0017, 0x008C0019 };

u32 lbl_1_data_3C[5] = { 0x0072000B, 0x0072000C, 0x0072000D, 0x0072000E, 0x0072000F };

OMCAMERAVIEW lbl_1_data_50 = { { 0.0f, 241.9f, 304.5f }, { -14.8f, 0.0f, 0.0f }, 1933.0f };

HuVecF lbl_1_data_6C[4] = { { -1000.0f, 0.0f, 0.0f }, { -800.0f, 0.0f, 0.0f }, { 800.0f, 0.0f, 0.0f }, { 1000.0f, 0.0f, 0.0f } };
HuVecF lbl_1_data_9C[4] = { { -300.0f, 0.0f, 0.0f }, { -100.36f, 0.0f, 0.0f }, { 100.36f, 0.0f, 0.0f }, { 300.66f, 0.0f, 0.0f } };
HuVecF lbl_1_data_CC = { 400.0f, 110.0f, -950.0f };
HuVecF lbl_1_data_D8 = { 200.0f, 110.0f, -950.0f };
HuVecF lbl_1_data_E4 = { -100.0f, 8000.0f, 0.0f };    /* shadow position */
HuVecF lbl_1_data_F0 = { 0.0f, 1.0f, 0.0f };          /* shadow up */
HuVecF lbl_1_data_FC = { 0.0f, 0.0f, 0.0f };          /* shadow target */

MGSEQ_PARAM lbl_1_data_108 = {
    0, MGSEQ_TIMER_TOP,
    fn_1_20D8,
    fn_1_23C8,
    NULL,
    fn_1_25F8,
    fn_1_265C,
    fn_1_2714,
    fn_1_27A0,
    NULL,
    NULL
};

/* --- .bss (math.c owns bss_9B0..bss_BA8 and bss_BB8) --- */

ANIMDATA *lbl_1_bss_0;            /* billboard anim */
s32 lbl_1_bss_4;
s32 lbl_1_bss_8;
float lbl_1_bss_C;
s16 lbl_1_bss_10;
s16 lbl_1_bss_12;
HuVecF lbl_1_bss_14;
HuVecF lbl_1_bss_20;
HuVecF lbl_1_bss_2C;
s32 lbl_1_bss_38;
s32 lbl_1_bss_3C;
s32 lbl_1_bss_40;
s32 lbl_1_bss_44;                 /* HuAudSStreamPlay id */
HuVecF lbl_1_bss_48[48];
HuVecF lbl_1_bss_288[100];
s32 lbl_1_bss_738;                /* live fn_1_4910 objects */
s32 lbl_1_bss_73C;                /* live fn_1_41D4 objects */
s16 lbl_1_bss_740;
s16 lbl_1_bss_742;
s16 lbl_1_bss_744;
s16 lbl_1_bss_746[7];
OMOBJ *lbl_1_bss_754[48];
OMOBJ *lbl_1_bss_814[100];        /* dtk sizes this 0x194 */
OMOBJ **lbl_1_bss_9A8;            /* group 1: Bowser */
OMOBJ **lbl_1_bss_9AC;            /* group 0: players */
OMOBJMAN *lbl_1_bss_BB4;

/* Distance check the object inlines everywhere: XZ plane, squared radius. */
static inline s32 fn_1_DistCheck(HuVecF *a, HuVecF *b, float radius2)
{
    if(((a->x - b->x) * (a->x - b->x)) + ((a->z - b->z) * (a->z - b->z)) < radius2) {
        return 1;
    }
    return 0;
}

/* asm 61-449, 381 insns. */
void ObjectSetup(void)
{
    s32 i;
    OMOBJ *obj;

    OSReport("******* M559 ObjectSetup *********\n");
    lbl_1_bss_BB4 = omInitObjMan(200, 0x2000);
    omGameSysInit(lbl_1_bss_BB4);
    lbl_1_bss_12 = Hu3DMotionCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x10), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_10 = Hu3DModelCameraCreate(lbl_1_bss_12, 1);
    HuPrcVSleep();
    lbl_1_bss_C = Hu3DMotionMotionMaxTimeGet(lbl_1_bss_12);
    Hu3DCameraPosGet(1, &lbl_1_bss_2C, &lbl_1_bss_20, &lbl_1_bss_14);
    HuPrcVSleep();
    Hu3DModelKill(lbl_1_bss_10);
    HuPrcVSleep();
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPosSetV(1, &lbl_1_bss_2C, &lbl_1_bss_20, &lbl_1_bss_14);
    lbl_1_bss_744 = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DGLightPosAimSetV(lbl_1_bss_744, &lbl_1_data_0, &lbl_1_data_C);
    Hu3DGLightStaticSet(lbl_1_bss_744, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_744);
    Hu3DGLightColorSet(lbl_1_bss_744, lbl_1_data_18.r, lbl_1_data_18.g, lbl_1_data_18.b, lbl_1_data_18.a);
    Hu3DShadowCreate(10.0f, 10.0f, 10000.0f);
    Hu3DShadowColSet(16, 16, 16);
    Hu3DShadowPosSet(&lbl_1_data_E4, &lbl_1_data_F0, &lbl_1_data_FC);
    Hu3DShadowTPLvlSet(0.3f);
    omMakeGroupEx(lbl_1_bss_BB4, 0, 4);
    lbl_1_bss_9AC = omGetGroupMemberListEx(lbl_1_bss_BB4, 0);
    for(i = 0; i < 4; i++) {
        obj = omAddObjEx(lbl_1_bss_BB4, 100, 1, 8, 0, fn_1_694);
        lbl_1_bss_9AC[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M559_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    CharEffectLayerSet(4);
    omMakeGroupEx(lbl_1_bss_BB4, 3, 1);
    lbl_1_bss_9A8 = omGetGroupMemberListEx(lbl_1_bss_BB4, 3);
    obj = omAddObjEx(lbl_1_bss_BB4, 103, 1, 5, 3, fn_1_3068);
    lbl_1_bss_9A8[0] = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M559_KUPA), HU_MEMNUM_OVL);
    lbl_1_bss_0 = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_m559, 0x11), HU_MEMNUM_OVL));
    HuSprAnimLock(lbl_1_bss_0);
    lbl_1_bss_742 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x06), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_740 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x07), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_742, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_742, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_740, HU3D_ATTR_DISPOFF);
    lbl_1_bss_73C = 0;
    lbl_1_bss_738 = 0;
    for(i = 0; i < 100; i++) {
        lbl_1_bss_814[i] = NULL;
    }
    for(i = 0; i < 48; i++) {
        lbl_1_bss_754[i] = NULL;
    }
    omMakeGroupEx(lbl_1_bss_BB4, 1, 100);
    omGetGroupMemberListEx(lbl_1_bss_BB4, 1);
    omMakeGroupEx(lbl_1_bss_BB4, 2, 48);
    omGetGroupMemberListEx(lbl_1_bss_BB4, 2);
    fn_1_3A1C();
    fn_1_3DA8();
    lbl_1_bss_3C = 0;
    lbl_1_bss_38 = 0;
    fn_1_5564();
    MgSeqCreatePrio(&lbl_1_data_108, 1000);
}

/* asm 452-705, 242 insns. Player object init. */
void fn_1_694(OMOBJ *obj)
{
    M559_PLAYER *work;
    s32 i;
    s32 waitEasy;
    s32 waitNormal;
    s32 waitHard;
    s32 waitVeryHard;
    float posX;
    float posY;
    float posZ;

    work = obj->data;
    work->no = obj->work[0];
    work->charNo = GwPlayerConf[work->no].charNo;
    work->padNo = GwPlayerConf[work->no].padNo;
    work->stkX = work->stkY = 0.0f;
    work->mode = 0;
    work->timer = 0;
    work->unk68 = 0;
    obj->mdlId[0] = CharModelCreate(work->charNo, 2);
    for(i = 0; i < 8; i++) {
        obj->mtnId[i] = CharMotionCreate(work->charNo, lbl_1_data_1C[i]);
        CharMotionSet(work->charNo, obj->mtnId[i]);
    }
    work->motNo = 1;
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[1]);
    Hu3DModelShadowSet(obj->mdlId[0]);
    Hu3DModelLayerSet(obj->mdlId[0], 4);
    CharMotionUpdateSet(work->charNo, 0x008C0017, 0);
    work->dif = GwPlayerConf[work->no].dif;
    work->comWait = 0;
    work->comMode = 0;
    switch(work->dif) {
        case 0:
            waitEasy = frandmod(5) + 20;
            work->comWaitMax = waitEasy;
            break;
        case 1:
            waitNormal = frandmod(5) + 15;
            work->comWaitMax = waitNormal;
            break;
        case 2:
            waitHard = frandmod(4) + 6;
            work->comWaitMax = waitHard;
            break;
        case 3:
            waitVeryHard = frandmod(4) + 1;
            work->comWaitMax = waitVeryHard;
            break;
    }
    work->rot.x = work->rot.z = 0.0f;
    if(work->no < 2) {
        work->rot.y = 90.0f;
    } else {
        work->rot.y = -90.0f;
    }
    work->target.x = 0.0f;
    work->target.y = 0.0f;
    work->target.z = 0.0f;
    posZ = lbl_1_data_6C[work->no].z;
    posY = lbl_1_data_6C[work->no].y;
    posX = lbl_1_data_6C[work->no].x;
    work->pos.x = posX;
    work->pos.y = posY;
    work->pos.z = posZ;
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    work->mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x08), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(work->mdlId, 4);
    Hu3DModelAttrSet(work->mdlId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(work->mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(work->mdlId, work->pos.x, work->pos.y, work->pos.z);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    CharMotionDataClose(work->charNo);
    obj->objFunc = fn_1_A5C;
}

/* asm 708-1040, 315 insns. Player object main; 7-case switch (.data:0x154). */
void fn_1_A5C(OMOBJ *obj)
{
    M559_PLAYER *work;
    HuVecF screen;
    s16 pan;
    s16 panShift;
    s16 panSet;

    work = obj->data;
    Hu3D3Dto2D(&work->pos, 1, &screen);
    pan = 32.0f + ((screen.x / 576.0f) * 64.0f);
    panShift = pan;
    panSet = panShift;
    CharModelVoicePanSet(work->charNo, panSet);
    if(MgSeqModeGet() == MGSEQ_MODE_MAIN) {
        if(GwPlayerConf[work->no].type != 0) {
            if(work->dif == 0 || work->dif == 1) {
                fn_1_F48(obj);
            } else {
                fn_1_1070(obj);
            }
        } else {
            work->stkX = HuPadStkX[work->padNo];
            work->stkY = HuPadStkY[work->padNo];
        }
    }
    switch(work->mode) {
        case 0:
            fn_1_2948(obj, 1, 8.0f, HU3D_MOTATTR_LOOP);
            break;
        case 1:
            fn_1_2948(obj, 5, 8.0f, HU3D_MOTATTR_LOOP);
            if(work->timer > 90.0f) {
                work->timer = 0;
                work->rot.y = 0.0f;
                work->mode = 2;
                work->pos.x = lbl_1_data_9C[work->no].x;
                work->pos.y = lbl_1_data_9C[work->no].y;
                work->pos.z = lbl_1_data_9C[work->no].z;
                fn_1_2948(obj, 7, 8.0f, HU3D_MOTATTR_LOOP);
            } else {
                if(work->no < 2) {
                    work->pos.x += 7.7777777f;
                } else {
                    work->pos.x -= 7.7777777f;
                }
                work->timer++;
            }
            break;
        case 2:
            work->posOld = work->pos;
            if(MgSeqModeGet() == MGSEQ_MODE_MAIN) {
                fn_1_1B1C(work, obj);
            }
            break;
        case 3:
            fn_1_2948(obj, 1, 8.0f, HU3D_MOTATTR_NONE);
            if(work->timer > 40.0f) {
                work->timer = 0;
                work->mode = 4;
            } else {
                work->timer++;
                if(work->timer < 15) {
                    fn_1_5038(obj);
                }
            }
            break;
        case 4:
            fn_1_2948(obj, 6, 8.0f, HU3D_MOTATTR_LOOP);
            break;
        case 5:
            fn_1_2948(obj, 4, 8.0f, HU3D_MOTATTR_LOOP);
            if(work->timer > 30.0f) {
                work->timer = 0;
                work->mode = 6;
                fn_1_2948(obj, 1, 8.0f, HU3D_MOTATTR_LOOP);
            } else {
                work->rot.y += fn_1_5308(work->unk5C, 0, 30);
                work->timer++;
            }
            break;
        case 6:
            break;
    }
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    Hu3DModelPosSet(work->mdlId, work->pos.x, work->pos.y, work->pos.z);
}

/* asm 1043-1124, 74 insns. COM input for difficulty 0 and 1. */
void fn_1_F48(OMOBJ *obj)
{
    M559_PLAYER *work;

    work = obj->data;
    work->stkX = work->stkY = 0.0f;
    switch(work->comMode) {
        case 0:
            if(fn_1_1210(&work->target)) {
                work->comMode = 1;
            }
            break;
        case 1:
            work->comTimer++;
            if(work->comTimer > 120) {
                work->comTimer = 0;
                work->comMode = 0;
            } else if(fn_1_1894(obj)) {
                work->comMode = 2;
                work->stkX = work->stkY = 0.0f;
            }
            break;
        case 2:
            work->stkX = work->stkY = 0.0f;
            work->comWait++;
            if(work->comWait > work->comWaitMax) {
                work->comMode = 0;
                work->comWait = 0;
            }
            break;
    }
}

/* asm 1127-1239, 104 insns. COM input for difficulty 2 and 3. */
void fn_1_1070(OMOBJ *obj)
{
    M559_PLAYER *work;
    float radius;

    work = obj->data;
    if(work->unk68 != 0) {
        work->stkX = 0.0f;
        work->stkY = 0.0f;
    } else {
        if(work->dif == 2) {
            radius = 200.0f;
        } else {
            radius = 150.0f;
        }
        if(MgSeqFrameNoGet() == 35) {
            if(fn_1_1394(&work->pos, &work->target, radius)) {
                work->comMode = 1;
            }
        } else if(MgSeqFrameNoGet() == 230) {
            if(fn_1_1668(&work->pos, &work->target, radius)) {
                work->comMode = 1;
            }
        }
        if(work->target.x != 0.0f || work->target.z != 0.0f) {
            if(fn_1_19D8(obj)) {
                work->stkX = 0.0f;
                work->stkY = 0.0f;
                work->pos.x = work->target.x;
                work->pos.y = work->target.y;
                work->pos.z = work->target.z;
                work->target.x = 0.0f;
                work->target.y = 0.0f;
                work->target.z = 0.0f;
            }
        }
    }
}

/*
 * asm 1242-1343, 97 insns. A random XZ point within 585 of the centre. There
 * is no return statement: the caller tests r3, which still holds the second
 * frandmod result (nonzero except one time in 1,300).
 */
s32 fn_1_1210(HuVecF *out)
{
    HuVecF center;
    HuVecF pos;
    u32 randX;
    u32 randZ;

    center.x = 0.0f;
    center.y = 0.0f;
    center.z = 0.0f;
    do {
        randX = frandmod(1300);
        pos.x = randX - 635.0f;
        pos.y = 0.0f;
        randZ = frandmod(1300);
        pos.z = randZ - 635.0f;
    } while(!fn_1_DistCheck(&center, &pos, 342225.0f));
    out->x = pos.x;
    out->y = 0.0f;
    out->z = pos.z;
}

/*
 * asm 1346-1540, 181 insns. As fn_1_1210, but also clear of every live
 * fn_1_41D4 object by 75. Two retail quirks: the second check passes the
 * address of the pos parameter itself, so it reads the pointer's bits as x
 * (about -0.0 for a GameCube heap pointer) and the next stack slot, center.y
 * (0), as z; and like fn_1_1210 it has no return statement. The radius
 * argument is not read.
 */
s32 fn_1_1394(HuVecF *pos, HuVecF *out, float radius)
{
    HuVecF center;
    HuVecF newPos;
    u32 randX;
    u32 randZ;
    s32 i;
    M559_ITEM *item;

    center.x = 0.0f;
    center.y = 0.0f;
    center.z = 0.0f;
    while(1) {
        randX = frandmod(1300);
        newPos.x = randX - 635.0f;
        newPos.y = 0.0f;
        randZ = frandmod(1300);
        newPos.z = randZ - 635.0f;
        if(!fn_1_DistCheck(&center, &newPos, 342225.0f)) {
            continue;
        }
        if(!fn_1_DistCheck(&newPos, (HuVecF *)&pos, 40000.0f)) {
            continue;
        }
        for(i = 0; i < 100; i++) {
            if(lbl_1_bss_814[i] != NULL) {
                item = lbl_1_bss_814[i]->data;
                if(fn_1_DistCheck(&item->pos, &newPos, 5625.0f)) {
                    break;
                }
            }
        }
        if(i == 100) {
            break;
        }
    }
    if(0.0f == newPos.x && 0.0f == newPos.z) {
        newPos.x = 0.1f;
    }
    out->x = newPos.x;
    out->y = 0.0f;
    out->z = newPos.z;
}

/* asm 1543-1692, 139 insns. As fn_1_1210, but clear of every live fn_1_4910 object by 75; pos and radius are not read. */
s32 fn_1_1668(HuVecF *pos, HuVecF *out, float radius)
{
    HuVecF center;
    HuVecF newPos;
    u32 randX;
    u32 randZ;
    s32 i;
    M559_ITEM *item;

    center.x = 0.0f;
    center.y = 0.0f;
    center.z = 0.0f;
    while(1) {
        randX = frandmod(1300);
        newPos.x = randX - 635.0f;
        newPos.y = 0.0f;
        randZ = frandmod(1300);
        newPos.z = randZ - 635.0f;
        if(!fn_1_DistCheck(&center, &newPos, 342225.0f)) {
            continue;
        }
        for(i = 0; i < 48; i++) {
            if(lbl_1_bss_754[i] != NULL) {
                item = lbl_1_bss_754[i]->data;
                if(fn_1_DistCheck(&item->pos, &newPos, 5625.0f)) {
                    break;
                }
            }
        }
        if(i == 48) {
            break;
        }
    }
    out->x = newPos.x;
    out->y = 0.0f;
    out->z = newPos.z;
}

/* asm 1695-1779, 81 insns. Stick toward target; 1 once within 5. */
s32 fn_1_1894(OMOBJ *obj)
{
    float limit = 25.001f;
    M559_PLAYER *work = obj->data;
    HuVecF dir;
    HuVecF stick;

    PSVECSubtract(&work->target, &work->pos, &dir);
    dir.y = 0.0f;
    if(PSVECSquareMag(&dir) < limit) {
        return 1;
    }
    PSVECNormalize(&dir, &dir);
    stick.x = dir.x;
    stick.y = dir.z;
    work->stkX = (s8)(56.0f * stick.x);
    work->stkY = (s8)(56.0f * -stick.y);
    return 0;
}

/* asm 1782-1866, 81 insns. Instruction-identical to fn_1_1894. */
s32 fn_1_19D8(OMOBJ *obj)
{
    float limit = 25.001f;
    M559_PLAYER *work = obj->data;
    HuVecF dir;
    HuVecF stick;

    PSVECSubtract(&work->target, &work->pos, &dir);
    dir.y = 0.0f;
    if(PSVECSquareMag(&dir) < limit) {
        return 1;
    }
    PSVECNormalize(&dir, &dir);
    stick.x = dir.x;
    stick.y = dir.z;
    work->stkX = (s8)(56.0f * stick.x);
    work->stkY = (s8)(56.0f * -stick.y);
    return 0;
}

/* asm 1869-2138, 259 insns. Walk from the stick. */
void fn_1_1B1C(M559_PLAYER *work, OMOBJ *obj)
{
    s32 motNo;

    work->vel.x = 0.0f;
    work->vel.y = 0.0f;
    work->vel.z = 0.0f;
    work->vel.x = 0.25f * work->stkX;
    work->vel.z = 0.25f * -work->stkY;
    motNo = 1;
    work->speed = sqrtf((work->vel.x * work->vel.x) + (work->vel.z * work->vel.z));
    if(0.0f < work->speed) {
        if(10.0f <= work->speed) {
            work->vel.x /= work->speed;
            work->vel.z /= work->speed;
            work->speed = 10.0f;
            work->vel.x = 10.0f * work->vel.x;
            work->vel.z = 10.0f * work->vel.z;
        }
        work->rot.y = fn_1_7290(work->rot.y, HuAtan(work->vel.x, work->vel.z), 0.4f);
        if(7.0f <= work->speed) {
            motNo = 5;
        } else {
            motNo = 4;
        }
    }
    PSVECAdd(&work->pos, &work->vel, &work->pos);
    fn_1_1F28(work);
    fn_1_29D8(obj);
    if(work->motNo != motNo) {
        work->motNo = motNo;
        Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[work->motNo], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    }
}

/* asm 2141-2253, 108 insns. Keep the player within 585 of the centre. */
void fn_1_1F28(M559_PLAYER *work)
{
    float x;
    float z;
    float mag;

    x = work->pos.x;
    z = work->pos.z;
    mag = sqrtf((x * x) + (z * z));
    if(585.0f < mag) {
        x /= mag;
        z /= mag;
        work->pos.x = 585.0f * x;
        work->pos.z = 585.0f * z;
    }
}

/* asm 2256-2445, 188 insns. MGSEQ init hook. */
void fn_1_20D8(s16 mode, s16 frameNo)
{
    lbl_1_bss_746[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x00), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_746[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x01), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_746[2] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x02), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_746[3] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x03), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_746[4] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x04), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_746[5] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x05), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_746[6] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x09), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_746[4], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_746[5], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_746[6], HU3D_MOTATTR_PAUSE);
    Hu3DModelShadowMapSet(lbl_1_bss_746[0]);
    Hu3DModelLayerSet(lbl_1_bss_746[0], 1);
    Hu3DModelLayerSet(lbl_1_bss_746[1], 1);
    Hu3DModelLayerSet(lbl_1_bss_746[2], 1);
    Hu3DModelLayerSet(lbl_1_bss_746[3], 1);
    Hu3DModelLayerSet(lbl_1_bss_746[4], 1);
    Hu3DModelLayerSet(lbl_1_bss_746[5], 1);
    Hu3DModelLayerSet(lbl_1_bss_746[6], 1);
    Hu3DModelAttrSet(lbl_1_bss_746[2], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_746[6], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_746[6], HU3D_ATTR_DISPOFF);
    Hu3DCameraPosSetV(1, &lbl_1_bss_2C, &lbl_1_bss_20, &lbl_1_bss_14);
    HuPrcVSleep();
    lbl_1_bss_10 = Hu3DModelCameraCreate(lbl_1_bss_12, 1);
    Hu3DMotionSpeedSet(lbl_1_bss_10, 1.0f);
    Hu3DCameraMotionStart(lbl_1_bss_10, 1);
    Hu3DModelAttrReset(lbl_1_bss_746[4], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_746[5], HU3D_MOTATTR_PAUSE);
    fn_1_40A4();
    fn_1_413C();
    fn_1_5578();
    MgSeqModeNext();
}

/* asm 2448-2605, 140 insns. MGSEQ fade-in hook: the opening, timed to the camera motion. */
void fn_1_23C8(s16 mode, s16 frameNo)
{
    M559_KUPA *kupa = lbl_1_bss_9A8[0]->data;
    M559_PLAYER *work;
    s32 i;
    s32 j;

    for(i = 0; i < lbl_1_bss_C; i++) {
        if(i == 20) {
            for(j = 0; j < 4; j++) {
                work = lbl_1_bss_9AC[j]->data;
                work->mode = 1;
            }
        }
        if(i == 80) {
            kupa->mode = 1;
        }
        if(i == 140) {
            lbl_1_bss_4 = HuAudFXPlayPan(2428, 55);
        }
        if(i == 280) {
            HuAudFXStop(lbl_1_bss_4);
        }
        if(i == 305) {
            HuAudFXPlay(2429);
            HuAudFXPlay(2430);
            for(j = 0; j < 4; j++) {
                work = lbl_1_bss_9AC[j]->data;
                omVibrate(work->no, 30, 12, 0);
            }
        }
        if(i == 445) {
            HuAudFXPlay(2431);
            for(j = 0; j < 4; j++) {
                work = lbl_1_bss_9AC[j]->data;
                omVibrate(work->no, 30, 12, 0);
            }
        }
        if(i == 400) {
            kupa->mode = 3;
        }
        if(i == 340) {
            Hu3DMotionTimeSet(lbl_1_bss_746[6], 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_746[6], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(lbl_1_bss_746[6], HU3D_ATTR_DISPOFF);
        }
        HuPrcVSleep();
    }
    MgSeqModeNext();
}

/* asm 2608-2637, 25 insns. MGSEQ main hook. */
void fn_1_25F8(s16 mode, s16 frameNo)
{
    fn_1_29D4();
    if(MgSeqFrameNoGet() == 5) {
        fn_1_54C4();
        lbl_1_bss_40 = HuAudFXPlay(2433);
    }
    if(MgSeqFrameNoGet() == 200) {
        fn_1_5514();
    }
    if(MgSeqFrameNoGet() == 330) {
        MgSeqModeNext();
    }
}

/* asm 2640-2691, 46 insns. MGSEQ finish hook. */
void fn_1_265C(s16 mode, s16 frameNo)
{
    s32 i;
    M559_PLAYER *work;

    if(MgSeqFrameNoGet() == 0) {
        fn_1_55A8();
        HuAudFXFadeOut(lbl_1_bss_40, 100);
        for(i = 0; i < 4; i++) {
            work = lbl_1_bss_9AC[i]->data;
            if(work->unk68 == 0) {
                fn_1_2948(lbl_1_bss_9AC[i], 1, 8.0f, HU3D_MOTATTR_LOOP);
            }
        }
    }
}

/* asm 2694-2734, 35 insns. MGSEQ pre-winner hook. */
void fn_1_2714(s16 mode, s16 frameNo)
{
    M559_PLAYER *work;
    s32 i;

    if(MgSeqFrameNoGet() == 0) {
        for(i = 0; i < 4; i++) {
            work = lbl_1_bss_9AC[i]->data;
            work->mode = 5;
            work->unk5C = work->rot.y;
            work->timer = 0;
        }
    }
    if(MgSeqFrameNoGet() > 60) {
        MgSeqModeNext();
    }
}

/* asm 2737-2850, 106 insns. MGSEQ winner hook: 10 coins to each player still standing. */
void fn_1_27A0(s16 mode, s16 frameNo)
{
    M559_KUPA *kupa = lbl_1_bss_9A8[0]->data;
    M559_PLAYER *work;
    s32 i;
    s32 no;

    if(MgSeqFrameNoGet() == 0) {
        for(i = 0; i < 4; i++) {
            work = lbl_1_bss_9AC[i]->data;
            if(work->unk68 == 0) {
                fn_1_2948(lbl_1_bss_9AC[work->no], 2, 8.0f, HU3D_MOTATTR_NONE);
                no = work->no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[no].mgCoinBonus = 10;
                }
            } else {
                Hu3DMotionOverlaySet(lbl_1_bss_9AC[work->no]->mdlId[0], lbl_1_bss_9AC[work->no]->mtnId[0]);
            }
        }
        if(fn_1_542C()) {
            fn_1_3854(lbl_1_bss_9A8[0], 4, 8.0f, HU3D_MOTATTR_NONE);
            HuAudJinglePlay(123);
        } else {
            fn_1_3854(lbl_1_bss_9A8[0], 3, 8.0f, HU3D_MOTATTR_NONE);
            HuAudJinglePlay(122);
        }
    }
}

/* asm 2853-2890, 35 insns. Player motion set. */
void fn_1_2948(OMOBJ *obj, s32 motNo, float shift, u32 attr)
{
    M559_PLAYER *work = obj->data;

    if(work->motNo != motNo) {
        work->motNo = motNo;
        CharMotionShiftSet(work->charNo, obj->mtnId[work->motNo], 0.0f, shift, attr);
    }
}

/* asm 2893-2895, 1 insn. Empty. */
void fn_1_29D4(void)
{
}

/*
 * asm 2898-3084, 180 insns. Push overlapping players apart (XZ, radius 100),
 * sharing the push by how far each moved this frame, then recurse on the one
 * pushed. The second share uses this player's move twice; the object has it.
 */
void fn_1_29D8(OMOBJ *obj)
{
    M559_PLAYER *work = obj->data;
    M559_PLAYER *other;
    s32 i;
    float move;
    float otherMove;
    float dist;
    float ratio;
    HuVecF dir;
    HuVecF normal;
    HuVecF myPos;
    HuVecF otherPos;

    PSVECSubtract(&work->pos, &work->posOld, &dir);
    move = PSVECMag(&dir);
    if(0.0f != move) {
        for(i = 0; i < 4; i++) {
            if(i != work->no) {
                other = lbl_1_bss_9AC[i]->data;
                myPos.x = work->pos.x;
                myPos.y = work->pos.y;
                myPos.z = work->pos.z;
                myPos.y = 0.0f;
                otherPos.x = other->pos.x;
                otherPos.y = other->pos.y;
                otherPos.z = other->pos.z;
                otherPos.y = 0.0f;
                PSVECSubtract(&myPos, &otherPos, &dir);
                dist = PSVECMag(&dir);
                if(dist >= 99.5f) {
                    continue;
                }
                PSVECSubtract(&other->pos, &other->posOld, &dir);
                otherMove = PSVECMag(&dir);
                PSVECSubtract(&myPos, &otherPos, &normal);
                PSVECNormalize(&normal, &normal);
                dist = 100.0f - dist;
                ratio = ((0.6f * otherMove) + (0.4f * move)) / (move + otherMove);
                work->pos.x += ratio * (dist * normal.x);
                work->pos.y += ratio * (dist * normal.y);
                work->pos.z += ratio * (dist * normal.z);
                ratio = ((0.6f * move) + (0.4f * move)) / (move + otherMove);
                if(other->unk68 == 0) {
                    other->pos.x += ratio * (dist * -normal.x);
                    other->pos.y += ratio * (dist * -normal.y);
                    other->pos.z += ratio * (dist * -normal.z);
                }
                fn_1_29D8(lbl_1_bss_9AC[i]);
            }
        }
    }
}

/* asm 3087-3329, 240 insns. Unreferenced: debug camera readout (m560's, verbatim). */
void fn_1_2CA8(void)
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
        omCameraViewSet(&lbl_1_data_50);
    }
}

/* asm 3332-3489, 154 insns. Bowser object init. */
void fn_1_3068(OMOBJ *obj)
{
    M559_KUPA *work = obj->data;
    s32 i;

    obj->mdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m559, 0x0A), HU_MEMNUM_OVL, HEAP_MODEL));
    for(i = 0; i < 5; i++) {
        obj->mtnId[i] = Hu3DJointMotion(obj->mdlId[0], HuDataSelHeapReadNum(lbl_1_data_3C[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    work->motNo = 5;
    fn_1_3854(obj, 0, 0.0f, HU3D_MOTATTR_LOOP);
    work->mdlId = obj->mdlId[0];
    work->pos.x = lbl_1_data_CC.x;
    work->pos.y = lbl_1_data_CC.y;
    work->pos.z = lbl_1_data_CC.z;
    work->rot.x = 0.0f;
    work->rot.y = -90.0f;
    work->rot.z = 0.0f;
    work->mode = 0;
    work->timer = 0;
    work->billMdlId = -1;
    Hu3DModelShadowSet(obj->mdlId[0]);
    Hu3DModelLayerSet(obj->mdlId[0], 4);
    work->billMdlId = fn_1_7E88(NULL, NULL, 512);
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    omSetSca(obj, 1.5f, 1.5f, 1.5f);
    obj->objFunc = fn_1_32D0;
}

/* asm 3492-3865, 353 insns. Bowser object main: mode 1 breathes fire from frame 30 to 90. */
void fn_1_32D0(OMOBJ *obj)
{
    BOOL fireF;
    M559_KUPA *work;
    HuVecF posHand;
    HuVecF posHead;
    HuVecF dir;
    float angle;

    fireF = FALSE;
    work = obj->data;
    switch(work->mode) {
        case 1:
            fn_1_3854(obj, 2, 8.0f, HU3D_MOTATTR_NONE);
            if(work->timer > 100) {
                work->timer = 0;
                fn_1_3854(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
                work->mode = 0;
            } else {
                if(work->timer >= 30 && work->timer < 90) {
                    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                    fireF = TRUE;
                    if(work->timer == 30) {
                        lbl_1_bss_8 = HuAudFXPlayPan(2427, fn_1_55D8(&work->pos));
                    }
                } else if(work->timer == 90) {
                    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                    fireF = FALSE;
                    HuAudFXStop(lbl_1_bss_8);
                }
                work->timer++;
            }
            break;
        case 3:
            work->pos.x = lbl_1_data_D8.x;
            work->pos.y = lbl_1_data_D8.y;
            work->pos.z = lbl_1_data_D8.z;
            work->rot.y = 0.0f;
            work->mode = 0;
            break;
        case 0:
        case 2:
            break;
    }
    if(work->billMdlId >= 0) {
        if(fireF) {
            fn_1_7400(obj->mdlId[0], "g000m0-itemhook_M", &posHand);
            fn_1_7400(obj->mdlId[0], "g000m0-ns_hed", &posHead);
            posHead.y += 100.0f;
            PSVECSubtract(&posHand, &posHead, &dir);
            angle = HuAtan(dir.x, dir.z);
            fn_1_7C28(work->billMdlId, 1, &posHand, angle, 250.0f, 0.0f);
        }
        if(fn_1_7B6C(work->billMdlId)) {
            work->billMdlId = -1;
        }
    }
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
}

/* asm 3868-3920, 49 insns. Bowser motion set, with his roars. */
void fn_1_3854(OMOBJ *obj, s32 motNo, float shift, u32 attr)
{
    M559_KUPA *work = obj->data;

    if(work->motNo != motNo) {
        work->motNo = motNo;
        Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[motNo], 0.0f, shift, attr);
        if(work->motNo == 3) {
            HuAudFXPlayPan(713, fn_1_55D8(&work->pos));
        }
        if(work->motNo == 4) {
            HuAudFXPlayPan(714, fn_1_55D8(&work->pos));
        }
    }
}

/*
 * asm 3923-3997, 65 insns. Is (x, z) in quadrant `side`? Called only inlined
 * (fn_1_3A1C, fn_1_3DA8). No return for a side above 3; nothing passes one.
 */
s32 fn_1_3918(s32 side, float x, float z)
{
    if(side == 0) {
        if(x < 0.0f && z < 0.0f) {
            return 1;
        } else {
            return 0;
        }
    } else if(side == 1) {
        if(x > 0.0f && z < 0.0f) {
            return 1;
        } else {
            return 0;
        }
    } else if(side == 2) {
        if(x < 0.0f && z > 0.0f) {
            return 1;
        } else {
            return 0;
        }
    } else if(side == 3) {
        if(x > 0.0f && z > 0.0f) {
            return 1;
        } else {
            return 0;
        }
    }
}

/* asm 4000-4244, 227 insns. Fill lbl_1_bss_288: 24 points per quadrant, then the four fixed ones. */
void fn_1_3A1C(void)
{
    HuVecF center;
    HuVecF newPos;
    u32 randX;
    u32 randZ;
    s32 side;
    s32 n;
    s32 idx;

    center.x = 0.0f;
    center.y = 0.0f;
    center.z = 0.0f;
    idx = 0;
    for(side = 0; side < 4; side++) {
        for(n = 0; n < 24; n++) {
            while(1) {
                randX = frandmod(1300);
                newPos.x = randX - 635.0f;
                newPos.y = 800.0f;
                randZ = frandmod(1300);
                newPos.z = randZ - 635.0f;
                if(!fn_1_DistCheck(&center, &newPos, 403225.0f)) {
                    continue;
                }
                if(fn_1_3918(side, newPos.x, newPos.z)) {
                    break;
                }
            }
            lbl_1_bss_288[idx].x = newPos.x;
            lbl_1_bss_288[idx].y = 800.0f;
            lbl_1_bss_288[idx].z = newPos.z;
            idx++;
        }
    }
    for(n = 0; n < 4; n++) {
        lbl_1_bss_288[idx].x = lbl_1_data_9C[n].x;
        lbl_1_bss_288[idx].y = lbl_1_data_9C[n].y;
        lbl_1_bss_288[idx].z = lbl_1_data_9C[n].z;
        idx++;
    }
}

/* asm 4247-4453, 191 insns. Fill lbl_1_bss_48: 12 points per quadrant. */
void fn_1_3DA8(void)
{
    HuVecF center;
    HuVecF newPos;
    u32 randX;
    u32 randZ;
    s32 side;
    s32 n;
    s32 idx;

    center.x = 0.0f;
    center.y = 0.0f;
    center.z = 0.0f;
    idx = 0;
    for(side = 0; side < 4; side++) {
        for(n = 0; n < 12; n++) {
            while(1) {
                randX = frandmod(1300);
                newPos.x = randX - 635.0f;
                newPos.y = 800.0f;
                randZ = frandmod(1300);
                newPos.z = randZ - 635.0f;
                if(!fn_1_DistCheck(&center, &newPos, 403225.0f)) {
                    continue;
                }
                if(fn_1_3918(side, newPos.x, newPos.z)) {
                    break;
                }
            }
            lbl_1_bss_48[idx].x = newPos.x;
            lbl_1_bss_48[idx].y = 800.0f;
            lbl_1_bss_48[idx].z = newPos.z;
            idx++;
        }
    }
}

/* asm 4456-4497, 38 insns. */
void fn_1_40A4(void)
{
    s32 i;
    float x;
    float z;

    for(i = 0; i < 100; i++) {
        x = lbl_1_bss_288[i].x;
        z = lbl_1_bss_288[i].z;
        fn_1_41D4(x, 800.0f, z);
    }
}

/* asm 4500-4541, 38 insns. */
void fn_1_413C(void)
{
    s32 i;
    float x;
    float z;

    for(i = 0; i < 48; i++) {
        x = lbl_1_bss_48[i].x;
        z = lbl_1_bss_48[i].z;
        fn_1_4910(x, 800.0f, z);
    }
}

/* asm 4544-4646, 100 insns. Create an item object (fn_1_4364), up to 100. */
void fn_1_41D4(float x, float y, float z)
{
    OMOBJ *obj;
    M559_ITEM *item;

    if(lbl_1_bss_73C > 99) {
        return;
    }
    obj = omAddObjEx(lbl_1_bss_BB4, 101, 1, 0, 1, fn_1_4364);
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M559_ITEM), HU_MEMNUM_OVL);
    item = obj->data;
    item->startPos.x = item->pos.x = x;
    item->startPos.y = item->pos.y = y;
    item->startPos.z = item->pos.z = z;
    item->rot.x = 0.0f;
    item->rot.y = 0.0f;
    item->rot.z = 0.0f;
    item->scale.x = item->scale.y = item->scale.z = 1.0f;
    item->mode = 0;
    item->delay = fn_1_7458(0, 45) + 15;
    item->timer = 0;
    item->fallTime = fn_1_7458(80, 100);
    item->fallSpeed = item->pos.y / item->fallTime;
    lbl_1_bss_73C++;
}

/* asm 4649-4758, 104 insns. Big item's first frame. */
void fn_1_4364(OMOBJ *obj)
{
    M559_ITEM *item = obj->data;
    s32 i;

    item->mdlId = Hu3DModelLink(lbl_1_bss_742);
    item->shadowMdlId = Hu3DModelLink(lbl_1_bss_740);
    item->unk54 = 0.0f;
    Hu3DModelAttrSet(item->mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(item->mdlId, 5);
    Hu3DModelLayerSet(item->shadowMdlId, 2);
    Hu3DModelPosSet(item->mdlId, item->pos.x, item->pos.y, item->pos.z);
    Hu3DModelPosSet(item->shadowMdlId, item->pos.x, 0.2f, item->pos.z);
    Hu3DModelScaleSet(item->shadowMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DMotionTimeSet(item->mdlId, frandmod(Hu3DMotionMaxTimeGet(item->mdlId)));
    for(i = 0; i < 100; i++) {
        if(NULL == lbl_1_bss_814[i]) {
            lbl_1_bss_814[i] = obj;
            break;
        }
    }
    Hu3DModelAttrSet(item->mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(item->shadowMdlId, HU3D_ATTR_DISPOFF);
    obj->objFunc = fn_1_4504;
}

/*
 * asm 4761-4986, 209 insns. Big item: 1 wait, 2 fall, 3 blink on the ground,
 * 4 gone. Below 150 it squashes any standing player within 55.
 */
void fn_1_4504(OMOBJ *obj)
{
    M559_ITEM *item = obj->data;
    M559_PLAYER *player;
    s32 i;

    switch(item->mode) {
        case 1:
            Hu3DModelAttrReset(item->mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(item->shadowMdlId, HU3D_ATTR_DISPOFF);
            item->timer++;
            if(item->timer > item->delay) {
                item->timer = 0;
                item->mode = 2;
            }
            break;
        case 2:
            item->pos.y -= item->fallSpeed;
            if(item->pos.y < 0.0f) {
                item->pos.y = 0.0f;
                item->mode = 3;
                item->timer = 0;
                if(lbl_1_bss_3C == 0) {
                    lbl_1_bss_3C = 1;
                    HuAudFXPlay(2434);
                }
            } else {
                item->timer++;
            }
            break;
        case 3:
            item->timer++;
            if(item->timer > 60) {
                item->timer = 0;
                item->mode = 4;
            }
            if(item->timer & 1) {
                Hu3DModelAttrSet(item->mdlId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(item->shadowMdlId, HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(item->mdlId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(item->shadowMdlId, HU3D_ATTR_DISPOFF);
            }
            break;
        case 4:
            fn_1_4848(obj);
            break;
        case 0:
            break;
    }
    if(item->pos.y < 150.0f) {
        for(i = 0; i < 4; i++) {
            player = lbl_1_bss_9AC[i]->data;
            if(fn_1_DistCheck(&player->pos, &item->pos, 3025.0f)) {
                if(player->unk68 == 0) {
                    player->mode = 3;
                    player->unk68 = 1;
                    Hu3DModelAttrReset(player->mdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(player->mdlId, HU3D_MOTATTR_PAUSE);
                    omVibrate(player->no, 30, 12, 0);
                    HuAudFXPlayVolPan(2435, fn_1_5654(&player->pos), fn_1_55D8(&player->pos));
                }
            }
        }
    }
    Hu3DModelPosSet(item->mdlId, item->pos.x, item->pos.y, item->pos.z);
    item->unk50 = 0.3f + (1.0f - (item->pos.y / item->startPos.y));
    Hu3DModelScaleSet(item->shadowMdlId, item->unk50, 1.0f, item->unk50);
    Hu3DModelPosSet(item->shadowMdlId, item->pos.x, 0.2f, item->pos.z);
}

/* asm 4989-5044, 50 insns. */
void fn_1_4848(OMOBJ *obj)
{
    M559_ITEM *item = obj->data;
    s32 i;

    Hu3DModelKill(item->mdlId);
    Hu3DModelKill(item->shadowMdlId);
    for(i = 0; i < 100; i++) {
        if(obj == lbl_1_bss_814[i]) {
            lbl_1_bss_814[i] = NULL;
            break;
        }
    }
    lbl_1_bss_73C--;
    omDelObjEx(lbl_1_bss_BB4, obj);
}

/* asm 5047-5148, 99 insns. Create an item object (fn_1_4A9C), up to 48. */
void fn_1_4910(float x, float y, float z)
{
    OMOBJ *obj;
    M559_ITEM *item;

    if(lbl_1_bss_738 > 47) {
        return;
    }
    obj = omAddObjEx(lbl_1_bss_BB4, 102, 1, 0, 2, fn_1_4A9C);
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M559_ITEM), HU_MEMNUM_OVL);
    item = obj->data;
    item->startPos.x = item->pos.x = x;
    item->startPos.y = item->pos.y = y;
    item->startPos.z = item->pos.z = z;
    item->rot.x = 0.0f;
    item->rot.y = 0.0f;
    item->rot.z = 0.0f;
    item->scale.x = item->scale.y = item->scale.z = 1.0f;
    item->mode = 0;
    item->delay = fn_1_7458(0, 45);
    item->timer = 0;
    item->fallTime = fn_1_7458(60, 80);
    item->fallSpeed = item->pos.y / item->fallTime;
    lbl_1_bss_738++;
}

/* asm 5151-5260, 104 insns. Small item's first frame. */
void fn_1_4A9C(OMOBJ *obj)
{
    M559_ITEM *item = obj->data;
    s32 i;

    item->mdlId = Hu3DModelLink(lbl_1_bss_742);
    item->shadowMdlId = Hu3DModelLink(lbl_1_bss_740);
    item->unk54 = 0.0f;
    Hu3DModelAttrSet(item->mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(item->mdlId, 5);
    Hu3DModelLayerSet(item->shadowMdlId, 2);
    Hu3DModelPosSet(item->mdlId, item->pos.x, item->pos.y, item->pos.z);
    Hu3DModelPosSet(item->shadowMdlId, item->pos.x, 0.2f, item->pos.z);
    Hu3DModelScaleSet(item->shadowMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DMotionTimeSet(item->mdlId, frandmod(Hu3DMotionMaxTimeGet(item->mdlId)));
    for(i = 0; i < 48; i++) {
        if(NULL == lbl_1_bss_754[i]) {
            lbl_1_bss_754[i] = obj;
            break;
        }
    }
    Hu3DModelAttrSet(item->mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(item->shadowMdlId, HU3D_ATTR_DISPOFF);
    obj->objFunc = fn_1_4C3C;
}

/* asm 5263-5484, 205 insns. As fn_1_4504 for the second wave; its own landing sound flag and shadow scale. */
void fn_1_4C3C(OMOBJ *obj)
{
    M559_ITEM *item = obj->data;
    M559_PLAYER *player;
    s32 i;

    switch(item->mode) {
        case 1:
            Hu3DModelAttrReset(item->mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(item->shadowMdlId, HU3D_ATTR_DISPOFF);
            item->timer++;
            if(item->timer > item->delay) {
                item->timer = 0;
                item->mode = 2;
            }
            break;
        case 2:
            item->pos.y -= item->fallSpeed;
            if(item->pos.y < 0.0f) {
                item->pos.y = 0.0f;
                item->mode = 3;
                item->timer = 0;
                if(lbl_1_bss_38 == 0) {
                    lbl_1_bss_38 = 1;
                    HuAudFXPlay(2434);
                }
            } else {
                item->timer++;
            }
            break;
        case 3:
            item->timer++;
            if(item->timer > 60) {
                item->timer = 0;
                item->mode = 4;
            }
            if(item->timer & 1) {
                Hu3DModelAttrSet(item->mdlId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(item->shadowMdlId, HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(item->mdlId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(item->shadowMdlId, HU3D_ATTR_DISPOFF);
            }
            break;
        case 4:
            fn_1_4F70(obj);
            break;
        case 0:
            break;
    }
    if(item->pos.y < 150.0f) {
        for(i = 0; i < 4; i++) {
            player = lbl_1_bss_9AC[i]->data;
            if(fn_1_DistCheck(&player->pos, &item->pos, 3025.0f)) {
                if(player->unk68 == 0) {
                    player->mode = 3;
                    player->unk68 = 1;
                    Hu3DModelAttrReset(player->mdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(player->mdlId, HU3D_MOTATTR_PAUSE);
                    omVibrate(player->no, 30, 12, 0);
                    HuAudFXPlayVolPan(2435, fn_1_5654(&player->pos), fn_1_55D8(&player->pos));
                }
            }
        }
    }
    Hu3DModelPosSet(item->mdlId, item->pos.x, item->pos.y, item->pos.z);
    item->unk50 = 1.3f - (item->pos.y / item->startPos.y);
    Hu3DModelScaleSet(item->shadowMdlId, item->unk50, 1.0f, item->unk50);
    Hu3DModelPosSet(item->shadowMdlId, item->pos.x, 0.2f, item->pos.z);
}

/* asm 5487-5542, 50 insns. */
void fn_1_4F70(OMOBJ *obj)
{
    M559_ITEM *item = obj->data;
    s32 i;

    Hu3DModelKill(item->mdlId);
    Hu3DModelKill(item->shadowMdlId);
    for(i = 0; i < 48; i++) {
        if(obj == lbl_1_bss_754[i]) {
            lbl_1_bss_754[i] = NULL;
            break;
        }
    }
    lbl_1_bss_738--;
    omDelObjEx(lbl_1_bss_BB4, obj);
}

/*
 * asm 5545-5738, 180 insns. Darken a squashed player's materials 10% a frame,
 * sparing the eyes (m560's M560PlayerBurn, verbatim, Waluigi case included).
 */
void fn_1_5038(OMOBJ *obj)
{
    M559_PLAYER *work = obj->data;
    BOOL burnF = TRUE;
    HU3DMODEL *modelP = &Hu3DData[obj->mdlId[0]];
    HSFDATA *hsf = modelP->hsf;
    HSFMATERIAL *material = hsf->material;
    char **eyeBmp;
    HSFATTRIBUTE *attr;
    int i;
    u32 j;

    if(work->charNo == 3) {
        for(i = 0; i < modelP->hsf->materialNum; i++, material++) {
            if(i == 1) {
                continue;
            }
            if(i == 2) {
                continue;
            }
            material->color[0] *= 0.9f;
            material->color[1] *= 0.9f;
            material->color[2] *= 0.9f;
        }
    } else {
        eyeBmp = CharModelEyeBmpGet(work->charNo, 2);
        for(i = 0; i < hsf->materialNum; i++, material++) {
            burnF = TRUE;
            for(j = 0; j < material->attrNum; j++) {
                attr = &hsf->attribute[material->attr[j]];
                if(strcmp(eyeBmp[0], attr->bitmap->name) == 0 || strcmp(eyeBmp[1], attr->bitmap->name) == 0) {
                    burnF = FALSE;
                }
            }
            if(burnF) {
                material->color[0] *= 0.9f;
                material->color[1] *= 0.9f;
                material->color[2] *= 0.9f;
            }
        }
    }
}

/* asm 5741-5819, 73 insns. Per-frame step to turn from angle `from` to `to` over `time` frames. */
float fn_1_5308(s32 from, s32 to, s32 time)
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

/* asm 5822-5865, 38 insns. TRUE when no player was squashed. */
BOOL fn_1_542C(void)
{
    M559_PLAYER *work[4];
    s32 i;

    for(i = 0; i < 4; i++) {
        work[i] = lbl_1_bss_9AC[i]->data;
    }
    if(work[0]->unk68 == 0 && work[1]->unk68 == 0 && work[2]->unk68 == 0 && work[3]->unk68 == 0) {
        return TRUE;
    }
    return FALSE;
}

/* asm 5868-5891, 20 insns. Release the first wave. */
void fn_1_54C4(void)
{
    s32 i;
    M559_ITEM *item;

    for(i = 0; i < 100; i++) {
        item = lbl_1_bss_814[i]->data;
        item->mode = 1;
    }
}

/* asm 5894-5917, 20 insns. Release the second wave. */
void fn_1_5514(void)
{
    s32 i;
    M559_ITEM *item;

    for(i = 0; i < 48; i++) {
        item = lbl_1_bss_754[i]->data;
        item->mode = 1;
    }
}

/* asm 5920-5926, 5 insns. */
void fn_1_5564(void)
{
    lbl_1_bss_44 = -1;
}

/* asm 5929-5942, 12 insns. */
void fn_1_5578(void)
{
    lbl_1_bss_44 = HuAudSStreamPlay(63);
}

/* asm 5945-5958, 12 insns. */
void fn_1_55A8(void)
{
    HuAudSStreamFadeOut(lbl_1_bss_44, 100);
}

/* asm 5961-5993, 31 insns. Pan for a 3D position. */
s16 fn_1_55D8(HuVecF *pos)
{
    HuVecF screen;
    s16 pan;

    Hu3D3Dto2D(pos, 1, &screen);
    pan = 32.0f + (64.0f * (screen.x / 576.0f));
    return pan;
}

/* asm 5996-6028, 31 insns. Volume for a 3D position. */
s16 fn_1_5654(HuVecF *pos)
{
    HuVecF screen;
    s16 vol;

    Hu3D3Dto2D(pos, 1, &screen);
    vol = 64.0f + (63.0f * (screen.y / 480.0f));
    return vol;
}
