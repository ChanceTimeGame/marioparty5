/*
 * m563dll -- four-player flower collecting in a castle garden pool (4P,
 * overlay 74).
 *
 * For 30 seconds flowers are thrown into the garden and pool; players walk,
 * jump and wade to collect them. Small flowers score 1, the one large flower
 * per 10-second phase scores 3. The top scorer wins +10 bonus coins; a tie
 * between two or more
 * players below 10 points is a draw.
 *
 * No upstream names or source exist, so functions keep their reference
 * addresses. Keep functions in the reference object's order: CodeWarrior's
 * auto-inlining depends on definition order, and math.c is included first
 * for the same reason (fn_1_66D4, fn_1_7290, fn_1_74F4 and fn_1_75B8 are
 * inlined into this file's code).
 */

#include "REL/m563dll/math.c"

#include "game/charman.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mg/actman.h"
#include "game/mg/score.h"
#include "game/mg/seqman.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/wipe.h"

#include "REL/m563Dll.h"

typedef struct M563Koopa_s {
    HuVecF pos; //0x00
    HuVecF rot; //0x0C
    HuVecF itemPos; //0x18
    HuVecF itemRot; //0x24
    HU3DMODELID itemMdlId; //0x30
    HU3DMODELID dropMdlId; //0x32
    HU3DMODELID mdlId[2]; //0x34
    int motNo[2]; //0x38
    int mode; //0x40
    int action; //0x44
    int time; //0x48
    int unk4C;
} M563_KOOPA;

typedef struct M563Player_s {
    int playerNo; //0x00
    int charNo; //0x04
    int score; //0x08
    HuVecF pos; //0x0C
    HuVecF rot; //0x18
    int unk24;
    int landWaveF; //0x28
    u32 groundAttr; //0x2C
    u32 comGroundAttr; //0x30
    float prevVelY; //0x34
    float velY; //0x38
    int wakeTime; //0x3C
    int unk40;
    HU3DMOTID motId[5]; //0x44
    s16 motNo; //0x4E
    s16 stepFx; //0x50
    int unk54;
    int unk58;
    HUSPRGRPID scoreWinId; //0x5C
    MGSCORE *scoreDisp; //0x60
    s16 espId; //0x64
    int comMode; //0x68
    int comDif; //0x6C
    HuVecF comTarget; //0x70
    float comRange; //0x7C
    int comTargetIdx; //0x80
    int comWaitMax; //0x84
    int comWait; //0x88
    int unk8C;
    int unk90;
    int unk94;
    int stkX; //0x98
    int stkY; //0x9C
    int btnDown; //0xA0
    int btn; //0xA4
    int comJumpTime; //0xA8
    int comJumpF; //0xAC
} M563_PLAYER;

typedef struct M563Coin_s {
    int slot; //0x00
    int timer; //0x04
    int state; //0x08
    HuVecF pos; //0x0C
    HuVecF endPos; //0x18
    HuVecF rot; //0x24
    HuVecF vel; //0x30
    int value; //0x3C
    int catchF; //0x40
    int waterF; //0x44
    float bobTime; //0x48
    int unk4C;
    int phase; //0x50
    int side; //0x54
    int posIdx; //0x58
    HuVecF target; //0x5C
} M563_COIN;

typedef struct M563CoinFx_s {
    HuVecF pos; //0x00
    int value; //0x0C
} M563_COINFX;

#define M563_COIN_FALL 1
#define M563_COIN_REST 0
#define M563_COIN_BLINK 2
#define M563_COIN_KILL 3

void ObjectSetup(void);
void fn_1_9A0(OMOBJ *obj);
void fn_1_EC0(OMOBJ *obj);
int fn_1_12A4(OMOBJ *obj);
void fn_1_1340(int no, int motNo, u32 attr);
void fn_1_13F4(int no, int motNo, u32 attr);
void fn_1_1488(OMOBJ *obj);
void fn_1_15AC(OMOBJ *obj);
void fn_1_162C(OMOBJ *obj);
void fn_1_16FC(OMOBJ *obj);
void fn_1_18BC(OMOBJ *obj);
void fn_1_1E7C(OMOBJ *obj);
void fn_1_2244(OMOBJ *obj);
BOOL fn_1_2998(OMOBJ *obj);
void fn_1_2AC0(OMOBJ *obj);
int fn_1_2B28(HuVecF *pos);
void fn_1_2B90(s16 mode, s16 frameNo);
void fn_1_2C5C(s16 mode, s16 frameNo);
void fn_1_2EB0(s16 mode, s16 frameNo);
void fn_1_2F34(s16 mode, s16 frameNo);
void fn_1_305C(s16 mode, s16 frameNo);
void fn_1_359C(s16 mode, s16 frameNo);
void fn_1_3A74(void);
void fn_1_3A78(void);
void fn_1_3AC4(void);
int fn_1_3EF0(void);
void fn_1_4068(OMOBJ *obj);
void fn_1_414C(float *outX, float *outZ, float minX, float minZ, float maxX, float maxZ);
void fn_1_41B0(OMOBJ *obj);
void fn_1_4334(OMOBJ *obj);
float fn_1_473C(float value, float range);
float fn_1_4868(float a, float b);
BOOL fn_1_49F4(HuVecF *a, float radiusA, HuVecF *b, float radiusB);
void fn_1_4BEC(float x, float y, float z);
void fn_1_4CB8(OMOBJ *obj);
void fn_1_4D2C(OMOBJ *obj);
void fn_1_4E54(OMOBJ *obj);
void fn_1_4F2C(float x, float y, float z, int value);
void fn_1_5004(OMOBJ *obj);
void fn_1_5078(OMOBJ *obj);
void fn_1_534C(OMOBJ *obj);
BOOL fn_1_5424(HuVecF *pos, HuVecF *out, float range);
BOOL fn_1_557C(HuVecF *pos, HuVecF *out);
BOOL fn_1_56C8(HuVecF *pos, HuVecF *out, int *idx, float range);
BOOL fn_1_5814(HuVecF *pos, HuVecF *out, float range, int *side, int *idx);
BOOL fn_1_5974(HuVecF *pos, HuVecF *out, float range);
BOOL fn_1_5A7C(HuVecF *pos);
void fn_1_5B14(int moveF);
void fn_1_5BC0(void);
BOOL fn_1_5D40(void);
void fn_1_5F14(OMOBJ *obj, int motNo, float shift, u32 attr);
void fn_1_6038(OMOBJ *obj, s16 stepFx);
void fn_1_60B4(OMOBJ *obj);
int fn_1_60D4(int min, int max);
float fn_1_6110(float x1, float z1, float x2, float z2);
void fn_1_6280(void);
void fn_1_660C(OMOBJ *obj);

/* Character name icons, indexed by character number. */
u32 lbl_1_data_0[13] = { 0x00960020, 0x00960021, 0x00960022, 0x00960023, 0x00960024, 0x00960026, 0x00960027, 0x00960028, 0x00960029,
    0x0096002A, 0x0096002B, 0x0096002C, 0x0096002D };

/* Idle, swim, win, lose, and one unused character motion. */
u32 lbl_1_data_34[5] = { 0x008C0000, 0x00870073, 0x008C0031, 0x008C0001, 0x008C0002 };

OMCAMERAVIEW lbl_1_data_48[2] = {
    { { 0.0f, 387.0f, -500.0f }, { 0.0f, 0.0f, 0.0f }, 500.0f },
    { { 0.0f, 985.0f, -500.0f }, { 0.0f, 0.0f, 0.0f }, 1009.0f },
};

OMCAMERAVIEW lbl_1_data_80 = { { 0.0f, 210.0f, 50.0f }, { -36.6f, 0.3f, 0.0f }, 2016.0f };
OMCAMERAVIEW lbl_1_data_9C = { { 0.0f, 386.86f, 50.0f }, { 1.57f, 0.3f, 0.0f }, 1522.0f };

HuVecF lbl_1_data_B8[4] = {
    { -480.0f, 243.0f, -315.0f },
    { 480.0f, 243.0f, -315.0f },
    { -430.0f, 93.0f, 310.0f },
    { 430.0f, 93.0f, 310.0f },
};

/* Result podium positions. */
HuVecF lbl_1_data_E8[4] = {
    { -239.66f, 137.86f, 297.0f },
    { -100.36f, 155.07f, 297.0f },
    { 100.36f, 155.07f, 297.0f },
    { 239.66f, 137.86f, 297.0f },
};

HuVecF lbl_1_data_118[2] = {
    { -50.0f, 300.0f, -895.0f },
    { 50.0f, 300.0f, -895.0f },
};

HuVecF lbl_1_data_130 = { 0.0f, 300.0f, -895.0f };

u32 lbl_1_data_13C[12] = { 0x00760017, 0x00760018, 0x00760019, 0x0076001A, 0x0076001B, 0x0076001C, 0x0076001D, 0x0076001E, 0x0076001F,
    0x00760020, 0x00760021, 0x00760022 };

HuVecF lbl_1_data_16C = { -5000.0f, 10000.0f, 0.0f };
HuVecF lbl_1_data_178 = { 0.0f, 0.0f, 0.0f };
GXColor lbl_1_data_184 = { 255, 255, 255, 255 };
HuVecF lbl_1_data_188 = { -100.0f, 8000.0f, 0.0f };
HuVecF lbl_1_data_194 = { 0.0f, 1.0f, 0.0f };
HuVecF lbl_1_data_1A0 = { 0.0f, 0.0f, 0.0f };

MGSEQ_PARAM lbl_1_data_1AC = { 30, MGSEQ_TIMER_TOP, fn_1_2B90, fn_1_2C5C, NULL, fn_1_2EB0, fn_1_2F34, fn_1_305C, fn_1_359C, NULL, NULL };

/* Landing-position indices used by fn_1_6280's opening throw. */
int lbl_1_data_1D4[4][3] = { { 17, 18, 20 }, { 1, 6, 12 }, { 17, 18, 20 }, { 1, 6, 12 } };

/* Per-quadrant bounds (min X, min Z, max X, max Z); unreferenced. */
float lbl_1_data_1D4_bounds[4][4] = {
    { -700.0f, -550.0f, 0.0f, 0.0f },
    { 0.0f, -550.0f, 700.0f, 0.0f },
    { -700.0f, 0.0f, 0.0f, 550.0f },
    { 0.0f, 0.0f, 700.0f, 550.0f },
};

/* Flower launch points, one per side. */
HuVecF lbl_1_data_244[4] = {
    { 900.0f, 2000.0f, 750.0f },
    { -900.0f, 2000.0f, 750.0f },
    { 900.0f, 2000.0f, -750.0f },
    { -900.0f, 2000.0f, -750.0f },
};

/* Side order per phase, cycled every 90 frames. */
int lbl_1_data_274[3][4] = { { 0, 1, 2, 3 }, { 1, 0, 3, 2 }, { 0, 3, 2, 1 } };

float lbl_1_data_2A4[4][2] = { { 64.0f, 60.0f }, { 168.0f, 60.0f }, { 408.0f, 60.0f }, { 512.0f, 60.0f } };

OMOBJ *lbl_1_bss_0;
BOOL lbl_1_bss_4;
int lbl_1_bss_8;
MGPLAYER *lbl_1_bss_14[4];
HU3DMOTID lbl_1_bss_24[12];
BOOL lbl_1_bss_3C;
int lbl_1_bss_40[3];
int lbl_1_bss_4C;
int lbl_1_bss_50[4];
int lbl_1_bss_60;
int lbl_1_bss_64;
int lbl_1_bss_68;
int lbl_1_bss_6C;
int lbl_1_bss_70;
float lbl_1_bss_74;
HU3DLIGHTID lbl_1_bss_78;
int lbl_1_bss_7C;
int lbl_1_bss_80;
int lbl_1_bss_84;
int lbl_1_bss_88;
int lbl_1_bss_8C;
int lbl_1_bss_90;
int lbl_1_bss_94;
int lbl_1_bss_98;
HuVecF lbl_1_bss_9C;
HuVecF lbl_1_bss_A8;
HuVecF lbl_1_bss_B4;
HuVecF lbl_1_bss_C0[4];
HU3DMODELID lbl_1_bss_F0[4];
HU3DMODELID lbl_1_bss_F8[12];
OMOBJ *lbl_1_bss_110;
OMOBJ *lbl_1_bss_118;
OMOBJ **lbl_1_bss_11C;
OMOBJ **lbl_1_bss_124;
OMOBJ **lbl_1_bss_128;
OMOBJ **lbl_1_bss_130;
OMOBJ *lbl_1_bss_134[30];
OMOBJMAN *lbl_1_bss_3B0;

#ifdef __MWERKS__
typedef void (*VoidFunc)(void);
extern const VoidFunc _ctors[];
extern const VoidFunc _dtors[];

int _prolog(void)
{
    const VoidFunc *ctors = _ctors;

    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
    ObjectSetup();
    return 0;
}

void _epilog(void)
{
    const VoidFunc *dtors = _dtors;

    while (*dtors != 0) {
        (**dtors)();
        dtors++;
    }
}
#endif

void ObjectSetup(void)
{
    OMOBJ *obj;
    int i;

    OSReport("******* M563 ObjectSetup *********\n");
    lbl_1_bss_3B0 = MgActorObjectSetup();
    mathMusicNo = -1;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    omCameraViewSet(lbl_1_data_48);
    lbl_1_bss_118 = omAddObjEx(lbl_1_bss_3B0, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_118->work[0] = 2;
    lbl_1_bss_78 = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DGLightPosAimSetV(lbl_1_bss_78, &lbl_1_data_16C, &lbl_1_data_178);
    Hu3DGLightStaticSet(lbl_1_bss_78, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_78);
    Hu3DGLightColorSet(lbl_1_bss_78, lbl_1_data_184.r, lbl_1_data_184.g, lbl_1_data_184.b, lbl_1_data_184.a);
    Hu3DShadowCreate(10.0f, 10.0f, 10000.0f);
    Hu3DShadowColSet(16, 16, 16);
    Hu3DShadowPosSet(&lbl_1_data_188, &lbl_1_data_194, &lbl_1_data_1A0);
    Hu3DShadowTPLvlSet(0.3f);
    lbl_1_bss_0 = omAddObjEx(lbl_1_bss_3B0, 103, 12, 0, -1, fn_1_18BC);
    omAddObjEx(lbl_1_bss_3B0, 103, 0, 0, -1, fn_1_1488);
    omMakeGroupEx(lbl_1_bss_3B0, 5, 1);
    lbl_1_bss_11C = omGetGroupMemberListEx(lbl_1_bss_3B0, 5);
    obj = omAddObjEx(lbl_1_bss_3B0, 105, 0, 0, 5, fn_1_9A0);
    lbl_1_bss_11C[0] = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M563_KOOPA), HU_MEMNUM_OVL);
    obj->work[0] = 0;
    fn_1_66D4();
    for (i = 0; i < 30; i++) {
        lbl_1_bss_134[i] = NULL;
    }
    omMakeGroupEx(lbl_1_bss_3B0, 1, 30);
    omGetGroupMemberListEx(lbl_1_bss_3B0, 1);
    lbl_1_bss_98 = 0;
    lbl_1_bss_90 = Hu3DModelCreateData(0x760000);
    Hu3DModelAttrSet(lbl_1_bss_90, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_90, HU3D_ATTR_NONE);
    lbl_1_bss_84 = Hu3DModelCreateData(0x760001);
    Hu3DModelAttrSet(lbl_1_bss_84, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_84, HU3D_ATTR_NONE);
    omMakeGroupEx(lbl_1_bss_3B0, 2, 30);
    lbl_1_bss_130 = omGetGroupMemberListEx(lbl_1_bss_3B0, 2);
    lbl_1_bss_94 = 0;
    lbl_1_bss_8C = Hu3DModelCreateData(0x76000C);
    Hu3DModelAttrSet(lbl_1_bss_8C, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_8C, HU3D_ATTR_NONE);
    lbl_1_bss_88 = Hu3DModelCreateData(0x76000D);
    Hu3DModelAttrSet(lbl_1_bss_88, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_88, HU3D_ATTR_NONE);
    omAddObjEx(lbl_1_bss_3B0, 101, 0, 0, -1, fn_1_162C);
    omAddObjEx(lbl_1_bss_3B0, 106, 0, 0, -1, fn_1_660C);
    lbl_1_bss_4 = FALSE;
    lbl_1_bss_8 = 0;
    omMakeGroupEx(lbl_1_bss_3B0, 0, 4);
    lbl_1_bss_124 = omGetGroupMemberListEx(lbl_1_bss_3B0, 0);
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(lbl_1_bss_3B0, 100, 0, 0, 0, fn_1_1E7C);
        lbl_1_bss_124[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M563_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    omMakeGroupEx(lbl_1_bss_3B0, 4, 10);
    lbl_1_bss_128 = omGetGroupMemberListEx(lbl_1_bss_3B0, 4);
    lbl_1_bss_80 = 0;
    lbl_1_bss_7C = Hu3DModelCreateData(0x76000E);
    Hu3DModelAttrSet(lbl_1_bss_7C, HU3D_ATTR_DISPOFF);
    lbl_1_bss_3C = FALSE;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_F0[i] = Hu3DModelCreateData(0x760002);
        lbl_1_bss_C0[i].x = lbl_1_data_E8[i].x;
        lbl_1_bss_C0[i].y = 135.0f + (800.0f + lbl_1_data_E8[i].y);
        lbl_1_bss_C0[i].z = lbl_1_data_E8[i].z;
        Hu3DModelPosSet(lbl_1_bss_F0[i], lbl_1_bss_C0[i].x, lbl_1_bss_C0[i].y, lbl_1_bss_C0[i].z);
        Hu3DModelRotSet(lbl_1_bss_F0[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrSet(lbl_1_bss_F0[i], HU3D_ATTR_DISPOFF);
    }
    MgSeqCreate(&lbl_1_data_1AC);
}

/* The two Koopa Troopas at the castle door (0x34/0x36, twelve joint motions),
 * the item one holds on "itemhook_r" (0x30) and the item's release model
 * played during the intro (0x32). The struct name is kept from that pair. */
void fn_1_9A0(OMOBJ *obj)
{
    M563_KOOPA *work;
    int i;

    work = obj->data;
    work->mdlId[0] = Hu3DModelCreateData(0x760015);
    work->mdlId[1] = Hu3DModelCreateData(0x760016);
    work->itemMdlId = Hu3DModelCreateData(0x760003);
    work->dropMdlId = Hu3DModelCreateData(0x760004);
    Hu3DModelAttrSet(work->dropMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(work->dropMdlId, HU3D_MOTATTR_PAUSE);
    Hu3DModelPosSet(work->dropMdlId, 50.0f, 300.0f, -620.0f);
    work->itemPos.x = 0.0f;
    work->itemPos.y = 0.0f;
    work->itemPos.z = 0.0f;
    work->itemRot.x = 0.0f;
    work->itemRot.y = 0.0f;
    work->itemRot.z = 0.0f;
    Hu3DModelPosSet(work->itemMdlId, work->itemPos.x, work->itemPos.y, work->itemPos.z);
    Hu3DModelRotSet(work->itemMdlId, work->itemRot.x, work->itemRot.y, work->itemRot.z);
    Hu3DModelHookSet(work->mdlId[1], "itemhook_r", work->itemMdlId);
    for (i = 0; i < 2; i++) {
        Hu3DModelAttrSet(work->mdlId[i], HU3D_MOTATTR_LOOP);
        Hu3DModelPosSet(work->mdlId[i], lbl_1_data_118[i].x, lbl_1_data_118[i].y, lbl_1_data_118[i].z);
        Hu3DModelRotSet(work->mdlId[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelShadowSet(work->mdlId[i]);
    }
    lbl_1_bss_24[0] = Hu3DJointMotionData(work->mdlId[0], lbl_1_data_13C[0]);
    lbl_1_bss_24[1] = Hu3DJointMotionData(work->mdlId[1], lbl_1_data_13C[1]);
    lbl_1_bss_24[2] = Hu3DJointMotionData(work->mdlId[0], lbl_1_data_13C[2]);
    lbl_1_bss_24[3] = Hu3DJointMotionData(work->mdlId[1], lbl_1_data_13C[3]);
    lbl_1_bss_24[4] = Hu3DJointMotionData(work->mdlId[0], lbl_1_data_13C[4]);
    lbl_1_bss_24[5] = Hu3DJointMotionData(work->mdlId[1], lbl_1_data_13C[5]);
    lbl_1_bss_24[6] = Hu3DJointMotionData(work->mdlId[0], lbl_1_data_13C[6]);
    lbl_1_bss_24[7] = Hu3DJointMotionData(work->mdlId[1], lbl_1_data_13C[7]);
    lbl_1_bss_24[8] = Hu3DJointMotionData(work->mdlId[1], lbl_1_data_13C[8]);
    lbl_1_bss_24[9] = Hu3DJointMotionData(work->mdlId[1], lbl_1_data_13C[9]);
    lbl_1_bss_24[10] = Hu3DJointMotionData(work->mdlId[0], lbl_1_data_13C[10]);
    lbl_1_bss_24[11] = Hu3DJointMotionData(work->mdlId[1], lbl_1_data_13C[11]);
    fn_1_1340(0, 0, HU3D_MOTATTR_LOOP);
    fn_1_1340(1, 8, HU3D_MOTATTR_LOOP);
    work->pos.x = lbl_1_data_130.x;
    work->pos.y = lbl_1_data_130.y;
    work->pos.z = lbl_1_data_130.z;
    work->rot.x = work->rot.y = work->rot.z = 0.0f;
    work->mode = 1;
    work->action = 1;
    work->time = 0;
    obj->objFunc = fn_1_EC0;
}

void fn_1_EC0(OMOBJ *obj)
{
    M563_KOOPA *work;

    work = obj->data;
    switch (work->mode) {
        case 0:
            fn_1_1340(0, 2, HU3D_MOTATTR_LOOP);
            fn_1_1340(1, 3, HU3D_MOTATTR_LOOP);
            work->pos.z += 1.8333334f;
            Hu3DModelPosSet(work->mdlId[0], work->pos.x - 50.0f, work->pos.y, work->pos.z);
            Hu3DModelPosSet(work->mdlId[1], 50.0f + work->pos.x, work->pos.y, work->pos.z);
            break;
        case 1:
            fn_1_1340(0, 0, HU3D_MOTATTR_LOOP);
            fn_1_1340(1, 9, HU3D_MOTATTR_LOOP);
            break;
        case 2:
            fn_1_13F4(1, 8, 0);
            break;
        case 3:
            fn_1_1340(0, 0, HU3D_MOTATTR_LOOP);
            fn_1_1340(1, 9, 0);
            break;
        case 4:
            fn_1_1340(0, 0, HU3D_MOTATTR_LOOP);
            fn_1_1340(1, 1, HU3D_MOTATTR_LOOP);
            break;
        case 5:
            fn_1_1340(0, 0, HU3D_MOTATTR_LOOP);
            fn_1_1340(1, 1, HU3D_MOTATTR_LOOP);
            work->time++;
            if (work->time > 60) {
                work->mode = fn_1_12A4(obj);
                work->time = 0;
            }
            break;
        case 6:
            fn_1_1340(0, 4, 0);
            fn_1_1340(1, 5, 0);
            work->time++;
            if (work->time > 308) {
                work->mode = 5;
                work->time = 0;
            }
            break;
        case 7:
            fn_1_1340(0, 4, 0);
            fn_1_1340(1, 7, 0);
            work->time++;
            if (work->time > 308) {
                work->mode = 5;
                work->time = 0;
            }
            break;
        case 8:
            fn_1_1340(0, 6, 0);
            fn_1_1340(1, 7, 0);
            work->time++;
            if (work->time > 308) {
                work->mode = 5;
                work->time = 0;
            }
            break;
        case 9:
            fn_1_1340(0, 10, HU3D_MOTATTR_LOOP);
            fn_1_1340(1, 11, HU3D_MOTATTR_LOOP);
            break;
        case 10:
            fn_1_1340(0, 2, HU3D_MOTATTR_LOOP);
            fn_1_1340(1, 3, HU3D_MOTATTR_LOOP);
            work->rot.y -= 6.0f;
            Hu3DModelRotSet(work->mdlId[0], work->rot.x, work->rot.y, work->rot.z);
            Hu3DModelRotSet(work->mdlId[1], work->rot.x, 360.0f - work->rot.y, work->rot.z);
            break;
        case 11:
            fn_1_1340(0, 2, HU3D_MOTATTR_LOOP);
            fn_1_1340(1, 3, HU3D_MOTATTR_LOOP);
            work->pos.z -= 2.2916667f;
            Hu3DModelPosSet(work->mdlId[0], work->pos.x - 50.0f, work->pos.y, work->pos.z);
            Hu3DModelPosSet(work->mdlId[1], 50.0f + work->pos.x, work->pos.y, work->pos.z);
            break;
    }
}

/* Pick the next taunt (modes 6-8), never repeating the last one. */
int fn_1_12A4(OMOBJ *obj)
{
    M563_KOOPA *work;
    int action;
    int rand;

    work = obj->data;
    do {
        rand = frandmod(3);
        switch (rand) {
            case 0:
                action = 6;
                break;
            case 1:
                action = 7;
                break;
            case 2:
                action = 8;
                break;
        }
    } while (action == work->action);
    work->action = action;
    return action;
}

void fn_1_1340(int no, int motNo, u32 attr)
{
    M563_KOOPA *work;

    work = lbl_1_bss_11C[0]->data;
    if (work->motNo[no] != motNo) {
        work->motNo[no] = motNo;
        Hu3DMotionShiftSet(work->mdlId[no], lbl_1_bss_24[motNo], 0.0f, 8.0f, attr);
    }
}

void fn_1_13F4(int no, int motNo, u32 attr)
{
    M563_KOOPA *work;

    work = lbl_1_bss_11C[0]->data;
    if (work->motNo[no] != motNo) {
        work->motNo[no] = motNo;
        Hu3DMotionSet(work->mdlId[no], lbl_1_bss_24[motNo]);
    }
}

void fn_1_1488(OMOBJ *obj)
{
    float texMtx[2][3] = { { 0.01f, 0.0f, 0.0f }, { 0.0f, 0.01f, 0.0f } };
    HuVecF posMin = { -500.0f, -10.0f, -350.0f };
    HuVecF posMax = { 500.0f, -10.0f, 800.0f };

    Hu3DWaterCreate(1, HU3D_WATER_ANIM_NONE, HU3D_WATER_ANIM_NONE, HU3D_WATER_ANIM_NONE, TRUE, &posMin, &posMax);
    Hu3DWaterTexScaleSet(1.5f, 3.0f, 1.5f);
    Hu3DWaterHiliteSet(0.3f);
    Hu3DWaterIndTexMtxSet(texMtx);
    lbl_1_bss_74 = 0.0f;
    obj->objFunc = fn_1_15AC;
}

void fn_1_15AC(OMOBJ *obj)
{
    lbl_1_bss_74 += 1.0f;
    Hu3DWaterTexPosSet(0.0005 * lbl_1_bss_74, 0.0f, 0.0f);
}

/* Flower spawner. */
void fn_1_162C(OMOBJ *obj)
{
    lbl_1_bss_70 = 0;
    lbl_1_bss_68 = 0;
    lbl_1_bss_64 = 0;
    lbl_1_bss_60 = 0;
    lbl_1_bss_4C = 0;
    fn_1_79E8();
    lbl_1_bss_40[0] = fn_1_60D4(1, 10);
    lbl_1_bss_40[1] = fn_1_60D4(11, 20);
    lbl_1_bss_40[2] = fn_1_60D4(21, 28);
    obj->objFunc = fn_1_16FC;
}

void fn_1_16FC(OMOBJ *obj)
{
    u32 time;

    if (MgSeqModeGet() > MGSEQ_MODE_START && MgSeqModeGet() <= MGSEQ_MODE_MAIN) {
        time = MgSeqTimerValueGet();
        time = time / 60;
        time = 30 - time;
        if (time != 0 && time < 11) {
            lbl_1_bss_70 = 0;
            lbl_1_bss_6C = 30;
        } else if (time > 10 && time < 21) {
            lbl_1_bss_70 = 1;
            lbl_1_bss_6C = 20;
        } else if (time > 20 && time < 30) {
            lbl_1_bss_70 = 2;
            lbl_1_bss_6C = 15;
        }
        lbl_1_bss_64++;
        if (lbl_1_bss_64 >= 90) {
            lbl_1_bss_64 = 0;
            lbl_1_bss_68++;
            if (lbl_1_bss_68 >= 4) {
                lbl_1_bss_68 = 0;
            }
        }
        lbl_1_bss_60++;
        if (lbl_1_bss_60 >= lbl_1_bss_6C) {
            lbl_1_bss_60 = 0;
            fn_1_3AC4();
        }
    }
}

void fn_1_18BC(OMOBJ *obj)
{
    COL_ATTRPARAM attrParam2;
    COL_ATTRPARAM attrParam4;
    MGACTOR_PARAM param;
    HU3DMODELID colMdlId[5];
    int i;

    lbl_1_bss_F8[0] = obj->mdlId[0] = Hu3DModelCreateData(0x760005);
    lbl_1_bss_F8[1] = obj->mdlId[1] = Hu3DModelCreateData(0x76000A);
    Hu3DModelAttrSet(lbl_1_bss_F8[1], HU3D_MOTATTR_LOOP);
    lbl_1_bss_F8[2] = obj->mdlId[2] = Hu3DModelCreateData(0x76000B);
    lbl_1_bss_F8[3] = obj->mdlId[3] = Hu3DModelCreateData(0x760006);
    lbl_1_bss_F8[4] = obj->mdlId[4] = Hu3DModelCreateData(0x760007);
    lbl_1_bss_F8[5] = obj->mdlId[5] = Hu3DModelCreateData(0x760008);
    lbl_1_bss_F8[6] = obj->mdlId[6] = Hu3DModelCreateData(0x760009);
    lbl_1_bss_F8[7] = obj->mdlId[7] = colMdlId[0] = Hu3DModelCreateData(0x76000F);
    lbl_1_bss_F8[8] = obj->mdlId[8] = colMdlId[1] = Hu3DModelCreateData(0x760010);
    lbl_1_bss_F8[9] = obj->mdlId[9] = colMdlId[2] = Hu3DModelCreateData(0x760011);
    lbl_1_bss_F8[10] = obj->mdlId[10] = colMdlId[3] = Hu3DModelCreateData(0x760012);
    lbl_1_bss_F8[11] = obj->mdlId[11] = colMdlId[4] = Hu3DModelCreateData(0x760013);
    Hu3DModelShadowMapSet(obj->mdlId[0]);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(obj->mdlId[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[4], HU3D_ATTR_NONE);
    Hu3DMotionSpeedSet(lbl_1_bss_F8[4], 0.0f);
    Hu3DMotionClusterSpeedSet(lbl_1_bss_F8[4], 0, 0.0f);
    Hu3DModelAttrSet(obj->mdlId[5], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(obj->mdlId[7], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[8], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[9], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[10], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[11], HU3D_ATTR_DISPOFF);
    param.height = 150.0f;
    param.radius = 50.0f;
    param.param = 0;
    param.type = 0;
    param.attr = 0;
    param.correctHookParam = 0;
    param.narrowHook = NULL;
    param.correctHook = NULL;
    MgActorColMapInit(colMdlId, 5, 9);
    attrParam2.speed = 0.7f;
    attrParam2.yDeviate = 1.0f;
    attrParam2.attr = 0;
    attrParam2.type = 1;
    attrParam2.maxDot = 1.0f;
    MgActorColAttrParamSet(&attrParam2, 2);
    attrParam4.speed = 1.0f;
    attrParam4.yDeviate = 0.0f;
    attrParam4.attr = 0;
    attrParam4.type = 1;
    attrParam4.maxDot = 1.0f;
    MgActorColAttrParamSet(&attrParam4, 4);
    for (i = 0; i < 4; i++) {
        lbl_1_bss_14[i] = MgPlayerCreate(i, &param, 2, 1, MGPLAYER_ACTFLAG_WALK | MGPLAYER_ACTFLAG_JUMP | MGPLAYER_ACTFLAG_STUN, NULL);
        MgPlayerVibrateCreate(lbl_1_bss_14[i]);
        param.param++;
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_14[i]->actor->pos.x = lbl_1_data_B8[i].x;
        lbl_1_bss_14[i]->actor->pos.y = lbl_1_data_B8[i].y;
        lbl_1_bss_14[i]->actor->pos.z = lbl_1_data_B8[i].z;
    }
    fn_1_5B14(0);
    for (i = 0; i < 4; i++) {
        Hu3DModelShadowSet(lbl_1_bss_14[i]->actor->mdlId);
        Hu3DModelLayerSet(lbl_1_bss_14[i]->actor->mdlId, 1);
    }
    obj->objFunc = NULL;
}

void fn_1_1E7C(OMOBJ *obj)
{
    M563_PLAYER *work;
    int i;

    work = obj->data;
    work->playerNo = obj->work[0];
    work->charNo = GwPlayerConf[work->playerNo].charNo;
    work->score = 0;
    work->prevVelY = 0.0f;
    work->velY = 0.0f;
    work->stkX = 0;
    work->stkY = 0;
    work->btnDown = 0;
    work->comJumpTime = 0;
    work->btn = 0;
    work->wakeTime = 0;
    for (i = 0; i < 5; i++) {
        work->motId[i] = CharMotionCreate(work->charNo, lbl_1_data_34[i]);
    }
    work->motNo = 5;
    work->stepFx = 0;
    work->comMode = 2;
    work->comDif = GwPlayerConf[work->playerNo].dif;
    work->unk8C = 0;
    work->comJumpF = 0;
    work->comWait = 0;
    switch (work->comDif) {
        case 0:
            work->comRange = 50.0f;
            work->comRange = 800.0f;
            work->comWaitMax = fn_1_60D4(50, 60);
            break;
        case 1:
            work->comRange = 250.0f;
            work->comRange = 800.0f;
            work->comWaitMax = fn_1_60D4(35, 45);
            break;
        case 2:
            work->comRange = 550.0f;
            work->comRange = 800.0f;
            work->comWaitMax = fn_1_60D4(10, 25);
            break;
        case 3:
            work->comRange = 800.0f;
            work->comWaitMax = fn_1_60D4(1, 5);
            break;
    }
    OSReport("%d pdp->SearchWaitMax:%d\n", work->playerNo, work->comWaitMax);
    work->scoreWinId = MgScoreWinCreate(96, 40);
    MgScoreWinTPLvlSet(work->scoreWinId, 0.85f);
    MgScoreWinPosSet(work->scoreWinId, lbl_1_data_2A4[work->playerNo][0], lbl_1_data_2A4[work->playerNo][1]);
    MgScoreWinDispSet(work->scoreWinId, FALSE);
    work->espId = espEntry(lbl_1_data_0[work->charNo], 0, 0);
    espDispOff(work->espId);
    espDrawNoSet(work->espId, 0);
    espPosSet(work->espId, lbl_1_data_2A4[work->playerNo][0] - 24.0f, lbl_1_data_2A4[work->playerNo][1]);
    espAttrSet(work->espId, 1);
    work->scoreDisp = MgScoreCreate(0x960031, -1, TRUE);
    MgScoreValueSet(work->scoreDisp, work->score);
    MgScorePosSet(work->scoreDisp, 8.0f + lbl_1_data_2A4[work->playerNo][0], lbl_1_data_2A4[work->playerNo][1]);
    MgScoreMaxDigitSet(work->scoreDisp, 2);
    MgScoreDispOff(work->scoreDisp);
    obj->objFunc = fn_1_2244;
}

void fn_1_2244(OMOBJ *obj)
{
    M563_PLAYER *work;
    BOOL moveF;
    u32 mode;
    HuVecF wavePos;

    work = obj->data;
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
        if (lbl_1_bss_14[work->playerNo]->motNo == MGPLAYER_MOT_WALK || lbl_1_bss_14[work->playerNo]->motNo == MGPLAYER_MOT_RUN) {
            moveF = TRUE;
        } else {
            moveF = FALSE;
        }
        work->comGroundAttr = lbl_1_bss_14[work->playerNo]->actor->colGroundAttr;
        if (GwPlayerConf[work->playerNo].type != 0) {
            work->stkX = 0;
            work->stkY = 0;
            work->btnDown = 0;
            if (work->comJumpTime == 0) {
                work->btn = 0;
            }
            switch (work->comMode) {
                case 0:
                    if (fn_1_56C8(&work->pos, &work->comTarget, &work->comTargetIdx, work->comRange)) {
                        work->comMode = 1;
                    } else {
                        work->comMode = 2;
                    }
                    break;
                case 1:
                    if (fn_1_2998(obj)) {
                        work->comMode = 2;
                    } else if (work->comGroundAttr & 0xBF80) {
                        if (work->comJumpF == 0) {
                            work->btnDown |= PAD_BUTTON_A;
                            work->btn |= PAD_BUTTON_A;
                            work->comJumpF = 1;
                        }
                    } else {
                        work->comJumpF = 0;
                        work->comJumpTime = 0;
                    }
                    if (work->comJumpF != 0) {
                        if (work->comJumpTime < 10) {
                            work->comJumpTime++;
                            work->btnDown |= PAD_BUTTON_A;
                            work->btn |= PAD_BUTTON_A;
                        } else {
                            work->comJumpF = 0;
                        }
                    }
                    break;
                case 2:
                    work->comWait++;
                    if (work->comWait > work->comWaitMax) {
                        work->comMode = 0;
                        work->comWait = 0;
                    }
                    break;
            }
            MgPlayerPadSet(lbl_1_bss_14[work->playerNo], work->stkX, work->stkY, work->btnDown, work->btn);
        }
        if (0.0f == lbl_1_bss_14[work->playerNo]->actor->velY) {
            work->groundAttr = lbl_1_bss_14[work->playerNo]->actor->colGroundAttr;
        } else {
            work->landWaveF = 0;
            work->unk24 = 0;
        }
        work->prevVelY = work->velY;
        work->velY = lbl_1_bss_14[work->playerNo]->actor->velY;
        if (0.0f == work->prevVelY && work->velY > work->prevVelY && (work->groundAttr & 2)) {
            fn_1_4BEC(work->pos.x, -10.0f, work->pos.z);
            wavePos.x = work->pos.x;
            wavePos.y = 5.0f + work->pos.y;
            wavePos.z = work->pos.z;
            Hu3DWaterWaveCreate(&wavePos, 100.0f, 300.0f);
        }
        if (0.0f == lbl_1_bss_14[work->playerNo]->actor->velY && (work->groundAttr & 2) && work->landWaveF == 0) {
            fn_1_4BEC(work->pos.x, -10.0f, work->pos.z);
            wavePos.x = work->pos.x;
            wavePos.y = 5.0f + work->pos.y;
            wavePos.z = work->pos.z;
            Hu3DWaterWaveCreate(&wavePos, 100.0f, 300.0f);
            work->landWaveF = 1;
        }
        if (work->groundAttr == 2) {
            CharModelFxFlagSet(work->charNo, FALSE);
            CharModelFxFlagSet(work->charNo, FALSE);
            fn_1_6038(lbl_1_bss_124[work->playerNo], 3);
            if (moveF) {
                work->wakeTime++;
                if (work->wakeTime > 30) {
                    wavePos.x = work->pos.x;
                    wavePos.y = 5.0f + work->pos.y;
                    wavePos.z = work->pos.z;
                    Hu3DWaterWaveCreate(&wavePos, 100.0f, 300.0f);
                    work->wakeTime = 0;
                }
            } else {
                work->wakeTime = 0;
            }
        } else {
            work->wakeTime = 0;
            CharModelFxFlagSet(work->charNo, TRUE);
            CharModelFxFlagSet(work->charNo, TRUE);
            fn_1_6038(lbl_1_bss_124[work->playerNo], 0);
        }
    }
    mode = MgSeqModeGet();
    if (mode == MGSEQ_MODE_MAIN || mode == MGSEQ_MODE_FINISH || mode == MGSEQ_MODE_PREWIN || mode == MGSEQ_MODE_WINNER) {
        MgScoreWinDispSet(work->scoreWinId, TRUE);
        espDispOn(work->espId);
        if (work->score <= 99) {
            MgScoreDispOn(work->scoreDisp);
            MgScoreValueSet(work->scoreDisp, work->score);
        }
    }
    work->pos.x = lbl_1_bss_14[work->playerNo]->actor->pos.x;
    work->pos.y = lbl_1_bss_14[work->playerNo]->actor->pos.y;
    work->pos.z = lbl_1_bss_14[work->playerNo]->actor->pos.z;
    work->rot.x = 0.0f;
    work->rot.y = lbl_1_bss_14[work->playerNo]->actor->rotY;
    work->rot.z = 0.0f;
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
        CharModelVoicePanSet(work->charNo, fn_1_74F4(&work->pos, 48, 80));
        CharModelVoiceVolSet(work->charNo, fn_1_75B8(&work->pos, 96, 127));
    }
}

/* COM: steer toward the chosen flower. TRUE once it is gone or reached. */
BOOL fn_1_2998(OMOBJ *obj)
{
    HuVecF dir;
    HuVecF stk;
    float reachDist = 1600.001f;
    M563_PLAYER *work = obj->data;

    if (lbl_1_bss_134[work->comTargetIdx] == NULL) {
        return TRUE;
    }
    PSVECSubtract(&work->comTarget, &work->pos, &dir);
    dir.y = 0.0f;
    if (PSVECSquareMag(&dir) < reachDist) {
        return TRUE;
    }
    PSVECNormalize(&dir, &dir);
    stk.x = dir.x;
    stk.y = dir.z;
    work->stkX = (s8)(56.0f * stk.x);
    work->stkY = (s8)(56.0f * -stk.y);
    return FALSE;
}

/* Unreferenced: aim the COM at a random landing point in its quadrant. */
void fn_1_2AC0(OMOBJ *obj)
{
    M563_PLAYER *work;
    HuVecF target;

    work = obj->data;
    fn_1_7818(&target.x, &target.y, &target.z, fn_1_2B28(&work->pos));
    work->comTarget.x = target.x;
    work->comTarget.y = target.y;
    work->comTarget.z = target.z;
}

int fn_1_2B28(HuVecF *pos)
{
    if (pos->x < 0.0f) {
        if (pos->z < 0.0f) {
            return 0;
        } else {
            return 2;
        }
    } else if (pos->z < 0.0f) {
        return 1;
    } else {
        return 3;
    }
}

void fn_1_2B90(s16 mode, s16 frameNo)
{
    M563_PLAYER *work;
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_124[i]->data;
        for (j = 0; j < 5; j++) {
            work->motId[j] = CharMotionCreate(lbl_1_bss_14[work->playerNo]->charNo, lbl_1_data_34[j]);
        }
    }
    if (!WipeCheckEnd()) {
        MgActorExec();
        MgSeqModeNext();
    }
}

/* Intro: the door Koopas release the item, then the camera pulls back and the
 * first volley of flowers lands. */
void fn_1_2C5C(s16 mode, s16 frameNo)
{
    M563_KOOPA *work;
    int i;

    work = lbl_1_bss_11C[0]->data;
    HuAudFXPlay(0x8D3);
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
    }
    Hu3DMotionSpeedSet(lbl_1_bss_F8[4], 1.0f);
    Hu3DMotionClusterSpeedSet(lbl_1_bss_F8[4], 0, 1.0f);
    HuAudFXPlay(0x8CB);
    for (i = 0; i < 120; i++) {
        HuPrcVSleep();
    }
    Hu3DMotionSpeedSet(lbl_1_bss_F8[4], 0.0f);
    Hu3DMotionClusterSpeedSet(lbl_1_bss_F8[4], 0, 0.0f);
    work->mode = 0;
    HuAudFXPlay(0x8CC);
    for (i = 0; i < 150; i++) {
        HuPrcVSleep();
    }
    work->mode = 3;
    for (i = 0; i < 60; i++) {
        HuPrcVSleep();
    }
    work->mode = 2;
    HuPrcVSleep();
    Hu3DModelHookObjReset(work->mdlId[1], "itemhook_r");
    Hu3DModelAttrSet(work->itemMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->dropMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->dropMdlId, HU3D_MOTATTR_PAUSE);
    Hu3DMotionTimeSet(work->dropMdlId, 0.0f);
    Hu3DMotionSpeedSet(work->dropMdlId, 1.0f);
    for (i = 0; i < 130; i++) {
        if (i == 45) {
            HuAudFXPlay(0x8CD);
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(work->dropMdlId, HU3D_ATTR_DISPOFF);
    work->mode = 4;
    omCameraViewMoveSimple(&lbl_1_data_80, 90);
    for (i = 0; i < 90; i++) {
        HuPrcVSleep();
    }
    Hu3DCameraPosGet(1, &lbl_1_bss_B4, &lbl_1_bss_A8, &lbl_1_bss_9C);
    fn_1_6280();
    HuAudFXPlay(0x8CF);
    mathMusicNo = HuAudSStreamPlay(0x35);
    MgSeqModeNext();
}

void fn_1_2EB0(s16 mode, s16 frameNo)
{
    M563_KOOPA *work;
    u32 time;

    fn_1_3A74();
    fn_1_3A78();
    if (MgSeqFrameNoGet() == 0) {
        work = lbl_1_bss_11C[0]->data;
        work->mode = 5;
    }
    time = MgSeqTimerValueGet();
    if (time == 0) {
        fn_1_5B14(0);
    } else {
        fn_1_5B14(1);
    }
    MgActorExec();
}

void fn_1_2F34(s16 mode, s16 frameNo)
{
    int unused = 0;
    M563_PLAYER *player;
    int i;
    M563_KOOPA *work;

    fn_1_3A78();
    if (MgSeqFrameNoGet() == 0) {
        HuAudSStreamFadeOut(mathMusicNo, 100);
        fn_1_5B14(0);
        work = lbl_1_bss_11C[0]->data;
        work->mode = 4;
        lbl_1_bss_3C = fn_1_5D40();
        lbl_1_bss_110 = omAddObjEx(lbl_1_bss_3B0, 100, 0, 0, -1, fn_1_60B4);
    }
    if (MgSeqFrameNoGet() > 300) {
        for (i = 0; i < 4; i++) {
            player = lbl_1_bss_124[i]->data;
            Hu3DModelAttrReset(lbl_1_bss_14[i]->actor->mdlId, HU3D_ATTR_DISPOFF);
        }
        MgSeqModeNext();
    }
}

/* Result staging: players are moved onto the podium and, unless the round
 * was a draw, prize models drop onto the winners. */
void fn_1_305C(s16 mode, s16 frameNo)
{
    M563_KOOPA *koopa;
    M563_PLAYER *work;
    int i;
    int j;

    koopa = lbl_1_bss_11C[0]->data;
    if (_CheckFlag(FLAGNUM(FLAG_GROUP_SYSTEM, 2))) {
        if (MgSeqFrameNoGet() == 30) {
            for (i = 0; i < 4; i++) {
                work = lbl_1_bss_124[i]->data;
                GWMgScoreSet(work->playerNo, work->score);
                OSReport("%d POINT:%d\n", work->playerNo, work->score);
            }
            MgSeqModeSet(MGSEQ_MODE_FADEOUT);
        }
    } else {
        fn_1_3A78();
        if (MgSeqFrameNoGet() == 30) {
            WipeCreate(2, 6, 30);
            WipeColorSet(255, 255, 255);
            do {
                HuPrcVSleep();
            } while (WipeCheckEnd());
            omDelObjEx(lbl_1_bss_3B0, lbl_1_bss_110);
            omCameraViewSet(&lbl_1_data_9C);
            if (lbl_1_bss_3C) {
                Hu3DModelAttrSet(lbl_1_bss_F8[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_F8[2], HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(lbl_1_bss_F8[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_F8[2], HU3D_ATTR_DISPOFF);
            }
            for (i = 0; i < 4; i++) {
                work = lbl_1_bss_124[i]->data;
                work->pos.x = lbl_1_data_E8[i].x;
                work->pos.y = lbl_1_data_E8[i].y;
                work->pos.z = lbl_1_data_E8[i].z;
                Hu3DModelPosSet(lbl_1_bss_14[i]->actor->mdlId, lbl_1_data_E8[i].x, lbl_1_data_E8[i].y - 75.0f, lbl_1_data_E8[i].z);
                Hu3DModelRotSet(lbl_1_bss_14[i]->actor->mdlId, 0.0f, 0.0f, 0.0f);
                Hu3DModelScaleSet(lbl_1_bss_14[i]->actor->mdlId, 1.0f, 1.0f, 1.0f);
                Hu3DModelAttrReset(lbl_1_bss_14[i]->actor->mdlId, HU3D_ATTR_DISPOFF);
                fn_1_5F14(lbl_1_bss_124[work->playerNo], 0, 0.0f, HU3D_MOTATTR_LOOP);
                lbl_1_bss_C0[i].x = lbl_1_data_E8[i].x;
                lbl_1_bss_C0[i].y = 135.0f + (800.0f + lbl_1_data_E8[i].y);
                lbl_1_bss_C0[i].z = lbl_1_data_E8[i].z;
                if (lbl_1_bss_50[work->playerNo] != -1) {
                    Hu3DModelAttrReset(lbl_1_bss_F0[work->playerNo], HU3D_ATTR_DISPOFF);
                }
            }
            WipeCreate(1, 5, 30);
            do {
                HuPrcVSleep();
            } while (WipeCheckEnd());
            if (!lbl_1_bss_3C) {
                lbl_1_bss_4 = TRUE;
                for (j = 0; j < 30; j++) {
                    for (i = 0; i < 4; i++) {
                        lbl_1_bss_C0[i].y -= 17.64151f;
                        Hu3DModelPosSet(lbl_1_bss_F0[i], lbl_1_bss_C0[i].x, lbl_1_bss_C0[i].y, lbl_1_bss_C0[i].z);
                    }
                    HuPrcVSleep();
                }
            }
            MgSeqModeNext();
        }
    }
}

void fn_1_359C(s16 mode, s16 frameNo)
{
    M563_KOOPA *koopa;
    M563_PLAYER *work;
    char *hookName;
    int i;

    koopa = lbl_1_bss_11C[0]->data;
    fn_1_3A78();
    if (!lbl_1_bss_3C) {
        if (MgSeqFrameNoGet() == 0) {
            for (i = 0; i < 4; i++) {
                work = lbl_1_bss_124[i]->data;
                if (lbl_1_bss_50[work->playerNo] == -1) {
                    fn_1_5F14(lbl_1_bss_124[work->playerNo], 2, 8.0f, 0);
                } else {
                    fn_1_5F14(lbl_1_bss_124[work->playerNo], 1, 8.0f, 0);
                    CharFXPlayPan(work->charNo, 0x1FA, fn_1_74F4(&work->pos, 48, 80));
                    GWMgCoinBonusAdd(work->playerNo, 10);
                    koopa->mode = 9;
                }
            }
        }
        if (MgSeqFrameNoGet() == 23) {
            for (i = 0; i < 4; i++) {
                work = lbl_1_bss_124[i]->data;
                if (lbl_1_bss_50[work->playerNo] != -1) {
                    hookName = CharModelItemHookGet(lbl_1_bss_14[work->playerNo]->charNo, 2, 0);
                    OSReport("FLO:%d\n", work->playerNo);
                    Hu3DModelPosSet(lbl_1_bss_F0[i], 0.0f, 0.0f, 0.0f);
                    Hu3DModelHookSet(lbl_1_bss_14[work->playerNo]->actor->mdlId, hookName, lbl_1_bss_F0[work->playerNo]);
                }
            }
        }
        if (MgSeqFrameNoGet() < 23) {
            for (i = 0; i < 4; i++) {
                lbl_1_bss_C0[i].y -= 15.094339f;
                Hu3DModelPosSet(lbl_1_bss_F0[i], lbl_1_bss_C0[i].x, lbl_1_bss_C0[i].y, lbl_1_bss_C0[i].z);
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            work = lbl_1_bss_124[i]->data;
            fn_1_5F14(lbl_1_bss_124[work->playerNo], 2, 8.0f, 0);
            CharFXPlay(work->charNo, 0x200);
        }
        koopa->mode = 10;
        for (i = 0; i < 30; i++) {
            HuPrcVSleep();
        }
        koopa->mode = 11;
        for (i = 0; i < 30; i++) {
            HuPrcVSleep();
        }
        Hu3DModelAttrSet(lbl_1_bss_F8[4], HU3D_MOTATTR_REV);
        Hu3DModelClusterAttrSet(lbl_1_bss_F8[4], 0, HU3D_CLUSTER_ATTR_REV);
        Hu3DMotionSpeedSet(lbl_1_bss_F8[4], 1.2f);
        Hu3DMotionClusterSpeedSet(lbl_1_bss_F8[4], 0, 1.2f);
        for (i = 0; i < 160; i++) {
            if (i == 80) {
                HuAudFXPlay(0x8D2);
            }
            HuPrcVSleep();
        }
        MgSeqModeNext();
    }
}

void fn_1_3A74(void)
{
}

void fn_1_3A78(void)
{
    M563_PLAYER *players[4];
    int i;

    for (i = 0; i < 4; i++) {
        players[i] = lbl_1_bss_124[i]->data;
    }
}

/* Throw one flower toward a free landing point on the current side. */
void fn_1_3AC4(void)
{
    HuVecF end;
    HuVecF start;
    int idx;
    OMOBJ *obj;
    M563_COIN *coin;
    BOOL waterF;
    float time;

    if (lbl_1_bss_98 <= 29) {
        do {
            waterF = fn_1_767C(&end.x, &end.y, &end.z, lbl_1_data_274[lbl_1_bss_70][lbl_1_bss_68], &idx);
        } while ((0.0f == end.x && 0.0f == end.z) || fn_1_79A8(lbl_1_data_274[lbl_1_bss_70][lbl_1_bss_68], idx));
        fn_1_79C8(lbl_1_data_274[lbl_1_bss_70][lbl_1_bss_68], idx, 1);
        start.x = lbl_1_data_244[lbl_1_data_274[lbl_1_bss_70][lbl_1_bss_68]].x;
        start.y = lbl_1_data_244[lbl_1_data_274[lbl_1_bss_70][lbl_1_bss_68]].y;
        start.z = lbl_1_data_244[lbl_1_data_274[lbl_1_bss_70][lbl_1_bss_68]].z;
        if (0.0f != end.x || 0.0f != end.z) {
            lbl_1_bss_98++;
            obj = omAddObjEx(lbl_1_bss_3B0, 101, 1, 0, 1, fn_1_41B0);
            obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M563_COIN), HU_MEMNUM_OVL);
            obj->work[0] = fn_1_3EF0();
            coin = obj->data;
            coin->target.x = end.x;
            coin->target.y = end.y;
            coin->target.z = end.z;
            coin->phase = lbl_1_bss_70;
            coin->side = lbl_1_data_274[lbl_1_bss_70][lbl_1_bss_68];
            coin->posIdx = idx;
            coin->bobTime = 0.0f;
            coin->state = M563_COIN_FALL;
            coin->catchF = FALSE;
            coin->rot.x = coin->rot.y = coin->rot.z = 0.0f;
            coin->pos.x = start.x;
            coin->pos.y = start.y;
            coin->pos.z = start.z;
            coin->endPos.x = end.x;
            coin->endPos.y = end.y;
            coin->endPos.z = end.z;
            coin->waterF = waterF;
            time = 90.0f + 0.23529413f * (frand() & 0xFF);
            coin->vel.x = (coin->endPos.x - coin->pos.x) / time;
            coin->vel.y = (coin->endPos.y - coin->pos.y) / time;
            coin->vel.z = (coin->endPos.z - coin->pos.z) / time;
        }
    }
}

/* TRUE for the single large flower of the current 10-second phase. */
int fn_1_3EF0(void)
{
    int bigF;
    u32 time;

    bigF = FALSE;
    time = MgSeqTimerValueGet();
    time = time / 60;
    time = 30 - time;
    if (time != 0 && time < 11) {
        if (time == lbl_1_bss_40[0] && lbl_1_bss_4C == 0) {
            bigF = TRUE;
            lbl_1_bss_4C++;
        } else {
            bigF = FALSE;
        }
    } else if (time > 10 && time < 21) {
        if (time == lbl_1_bss_40[1] && lbl_1_bss_4C == 1) {
            bigF = TRUE;
            lbl_1_bss_4C++;
        } else {
            bigF = FALSE;
        }
    } else if (time > 20 && time < 28) {
        if (time == lbl_1_bss_40[2] && lbl_1_bss_4C == 2) {
            bigF = TRUE;
            lbl_1_bss_4C++;
        } else {
            bigF = FALSE;
        }
    }
    return bigF;
}

void fn_1_4068(OMOBJ *obj)
{
    M563_COIN *work;
    int i;

    work = obj->data;
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelKill(obj->mdlId[0]);
    lbl_1_bss_98--;
    for (i = 0; i < 30; i++) {
        if (obj == lbl_1_bss_134[i]) {
            lbl_1_bss_134[i] = NULL;
            break;
        }
    }
    fn_1_79C8(work->side, work->posIdx, 0);
    omDelObjEx(lbl_1_bss_3B0, obj);
}

void fn_1_414C(float *outX, float *outZ, float minX, float minZ, float maxX, float maxZ)
{
    *outX = fn_1_473C(minX, maxX);
    *outZ = fn_1_473C(minZ, maxZ);
}

void fn_1_41B0(OMOBJ *obj)
{
    M563_COIN *work;
    int i;

    work = obj->data;
    if (obj->work[0] == 0) {
        obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_90);
        work->value = 1;
    } else {
        obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_84);
        work->value = 3;
    }
    Hu3DModelShadowSet(obj->mdlId[0]);
    Hu3DModelLayerSet(obj->mdlId[0], 2);
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 30; i++) {
        if (NULL == lbl_1_bss_134[i]) {
            lbl_1_bss_134[i] = obj;
            work->slot = i;
            break;
        }
    }
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    obj->objFunc = fn_1_4334;
}

void fn_1_4334(OMOBJ *obj)
{
    M563_COIN *work;
    M563_PLAYER *player;
    HuVecF wavePos;
    int i;

    work = obj->data;
    if (MgSeqModeGet() >= MGSEQ_MODE_FINISH && MgSeqFrameNoGet() == 0) {
        work->timer = 60;
        work->state = M563_COIN_BLINK;
    }
    switch (work->state) {
        case M563_COIN_FALL:
            work->pos.x += work->vel.x;
            work->pos.y += work->vel.y;
            work->pos.z += work->vel.z;
            work->rot.y += 10.0f;
            if (work->pos.y < work->endPos.y) {
                work->pos.y = work->endPos.y;
                work->state = M563_COIN_REST;
                work->timer = 120;
                if (work->waterF) {
                    wavePos.x = work->pos.x;
                    wavePos.y = 5.0f + work->pos.y;
                    wavePos.z = work->pos.z;
                    Hu3DWaterWaveCreate(&wavePos, 100.0f, 300.0f);
                }
            }
            break;
        case M563_COIN_REST:
            work->timer--;
            if (work->timer < 0) {
                work->timer = 120;
                work->state = M563_COIN_BLINK;
            }
            break;
        case M563_COIN_BLINK:
            work->timer--;
            if (work->timer < 0) {
                work->timer = 0;
                work->state = M563_COIN_KILL;
                return;
            }
            if (MgSeqFrameNoGet() & 1) {
                Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            }
            break;
        case M563_COIN_KILL:
            fn_1_4068(obj);
            return;
    }
    if (work->state == M563_COIN_REST || work->state == M563_COIN_BLINK) {
        work->catchF = TRUE;
    }
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
        for (i = 0; i < 4; i++) {
            player = lbl_1_bss_124[i]->data;
            if (fn_1_49F4(&work->pos, 40.0f, &player->pos, 50.0f)) {
                player->score += work->value;
                work->state = M563_COIN_KILL;
                fn_1_4F2C(work->pos.x, work->pos.y, work->pos.z, work->value);
                omVibrate(player->playerNo, 12, 6, 6);
                return;
            }
        }
    }
    if (work->state == M563_COIN_REST || work->state == M563_COIN_BLINK) {
        if (work->waterF) {
            work->pos.x += 0.3f * HuSin(work->bobTime);
            work->bobTime += 2.0f;
        }
    }
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
}

float fn_1_473C(float value, float range)
{
    float result;

    if (range == value) {
        result = range;
    }
    if (value < 0.0f) {
        value = fabs(value);
        result = value + (range - 0.003921569f * value * (frand() & 0xFF));
        result = -result;
    } else if (0.0f == value) {
        result = 0.003921569f * range * (frand() & 0xFF);
    }
    return result;
}

float fn_1_4868(float a, float b)
{
    float absA;
    float absB;
    float result;

    if (a < 0.0f && b < 0.0f) {
        absA = fabs(a);
        absB = fabs(b);
        result = absB + (absA - 0.003921569f * absB * (frand() & 0xFF));
    } else if (a >= 0.0f && b >= 0.0f) {
        result = a + (b - 0.003921569f * a * (frand() & 0xFF));
    }
    return result;
}

BOOL fn_1_49F4(HuVecF *a, float radiusA, HuVecF *b, float radiusB)
{
    float dx;
    float radius;
    float dy;
    float dz;
    float dist;

    dx = a->x - b->x;
    dy = a->y - b->y;
    dz = a->z - b->z;
    dist = sqrtf((dx * dx) + (dy * dy) + (dz * dz));
    radius = radiusA + radiusB;
    if (radius > dist) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* Splash when a player enters the water. */
void fn_1_4BEC(float x, float y, float z)
{
    OMOBJ *obj;
    HuVecF *pos;

    if (lbl_1_bss_80 <= 9) {
        lbl_1_bss_80++;
        obj = omAddObjEx(lbl_1_bss_3B0, 104, 1, 0, 4, fn_1_4D2C);
        obj->work[0] = 0;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(HuVecF), HU_MEMNUM_OVL);
        pos = obj->data;
        pos->x = x;
        pos->y = y;
        pos->z = z;
    }
}

void fn_1_4CB8(OMOBJ *obj)
{
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelKill(obj->mdlId[0]);
    lbl_1_bss_80--;
    omDelObjEx(lbl_1_bss_3B0, obj);
}

void fn_1_4D2C(OMOBJ *obj)
{
    HuVecF *pos;

    pos = obj->data;
    obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_7C);
    Hu3DModelLayerSet(obj->mdlId[0], 2);
    omSetTra(obj, pos->x, pos->y, pos->z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(obj->mdlId[0], 0.0f);
    Hu3DMotionSpeedSet(obj->mdlId[0], 1.0f);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_NONE);
    obj->objFunc = fn_1_4E54;
}

void fn_1_4E54(OMOBJ *obj)
{
    HuVecF *pos;

    pos = obj->data;
    if (Hu3DMotionEndCheck(obj->mdlId[0])) {
        fn_1_4CB8(obj);
    } else {
        omSetTra(obj, pos->x, pos->y, pos->z);
        omSetRot(obj, 0.0f, 0.0f, 0.0f);
    }
}

/* Flower pickup effect. The cap tests the splash count, as in the original. */
void fn_1_4F2C(float x, float y, float z, int value)
{
    OMOBJ *obj;
    M563_COINFX *work;

    if (lbl_1_bss_80 <= 29) {
        lbl_1_bss_94++;
        obj = omAddObjEx(lbl_1_bss_3B0, 101, 1, 0, 2, fn_1_5078);
        obj->work[0] = 0;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M563_COINFX), HU_MEMNUM_OVL);
        work = obj->data;
        work->pos.x = x;
        work->pos.y = y;
        work->pos.z = z;
        work->value = value;
    }
}

void fn_1_5004(OMOBJ *obj)
{
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelKill(obj->mdlId[0]);
    lbl_1_bss_94--;
    omDelObjEx(lbl_1_bss_3B0, obj);
}

void fn_1_5078(OMOBJ *obj)
{
    M563_COINFX *work;

    work = obj->data;
    if (work->value == 1) {
        obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_8C);
        HuAudFXPlayVolPan(0x8D0, fn_1_75B8(&work->pos, 96, 127), fn_1_74F4(&work->pos, 48, 80));
    } else {
        obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_88);
        HuAudFXPlayVolPan(0x8D1, fn_1_75B8(&work->pos, 96, 127), fn_1_74F4(&work->pos, 48, 80));
    }
    Hu3DModelLayerSet(obj->mdlId[0], 2);
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(obj->mdlId[0], 0.0f);
    Hu3DMotionSpeedSet(obj->mdlId[0], 1.0f);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_NONE);
    obj->objFunc = fn_1_534C;
}

void fn_1_534C(OMOBJ *obj)
{
    M563_COINFX *work;

    work = obj->data;
    if (Hu3DMotionEndCheck(obj->mdlId[0])) {
        fn_1_5004(obj);
    } else {
        omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
        omSetRot(obj, 0.0f, 0.0f, 0.0f);
    }
}

/* Unreferenced. The nearest-distance is never updated, so it never succeeds. */
BOOL fn_1_5424(HuVecF *pos, HuVecF *out, float range)
{
    HuVecF found;
    M563_COIN *coin;
    int i;
    float dist;
    float best;

    best = 1000000.0f;
    for (i = 0; i < 30; i++) {
        if (lbl_1_bss_134[i] != NULL) {
            coin = lbl_1_bss_134[i]->data;
            dist = fn_1_6110(pos->x, pos->z, coin->pos.x, coin->pos.z);
            if (dist < range && coin->catchF && fn_1_5A7C(&coin->pos) && best > dist) {
                found.x = coin->pos.x;
                found.y = coin->pos.y;
                found.z = coin->pos.z;
            }
        }
    }
    if (1000000.0f != best) {
        out->x = found.x;
        out->y = found.y;
        out->z = found.z;
        return TRUE;
    }
    return FALSE;
}

BOOL fn_1_557C(HuVecF *pos, HuVecF *out)
{
    HuVecF found;
    M563_COIN *coin;
    int i;
    float dist;
    float best;

    best = 1000000.0f;
    for (i = 0; i < 30; i++) {
        if (lbl_1_bss_134[i] != NULL) {
            coin = lbl_1_bss_134[i]->data;
            if (coin->catchF && fn_1_5A7C(&coin->pos)) {
                dist = fn_1_6110(pos->x, pos->z, coin->pos.x, coin->pos.z);
                if (best > dist) {
                    found.x = coin->pos.x;
                    found.y = coin->pos.y;
                    found.z = coin->pos.z;
                    best = dist;
                }
            }
        }
    }
    if (1000000.0f != best) {
        out->x = found.x;
        out->y = found.y;
        out->z = found.z;
        return TRUE;
    }
    return FALSE;
}

/* COM target search: nearest catchable flower inside the pool bounds. The
 * range argument is ignored. */
BOOL fn_1_56C8(HuVecF *pos, HuVecF *out, int *idx, float range)
{
    HuVecF found;
    M563_COIN *coin;
    int i;
    int foundIdx;
    float dist;
    float best;

    best = 1000000.0f;
    foundIdx = -1;
    for (i = 0; i < 30; i++) {
        if (lbl_1_bss_134[i] != NULL) {
            coin = lbl_1_bss_134[i]->data;
            if (coin->catchF && fn_1_5A7C(&coin->pos)) {
                dist = fn_1_6110(pos->x, pos->z, coin->pos.x, coin->pos.z);
                if (best > dist) {
                    found.x = coin->pos.x;
                    found.y = coin->pos.y;
                    found.z = coin->pos.z;
                    foundIdx = i;
                    best = dist;
                }
            }
        }
    }
    if (1000000.0f != best) {
        out->x = found.x;
        out->y = found.y;
        out->z = found.z;
        *idx = foundIdx;
        return TRUE;
    }
    return FALSE;
}

/* Unreferenced; shares fn_1_5424's missing best-distance update. */
BOOL fn_1_5814(HuVecF *pos, HuVecF *out, float range, int *side, int *idx)
{
    HuVecF found;
    M563_COIN *coin;
    int i;
    int foundSide;
    int foundIdx;
    float dist;
    float best;

    best = 1000000.0f;
    for (i = 0; i < 30; i++) {
        if (lbl_1_bss_134[i] != NULL) {
            coin = lbl_1_bss_134[i]->data;
            dist = fn_1_6110(pos->x, pos->z, coin->pos.x, coin->pos.z);
            if (dist < range && coin->catchF && fn_1_5A7C(&coin->pos) && best > dist) {
                found.x = coin->pos.x;
                found.y = coin->pos.y;
                found.z = coin->pos.z;
                foundSide = coin->side;
                foundIdx = coin->posIdx;
            }
        }
    }
    if (1000000.0f != best) {
        out->x = found.x;
        out->y = found.y;
        out->z = found.z;
        *side = foundSide;
        *idx = foundIdx;
        return TRUE;
    }
    return FALSE;
}

BOOL fn_1_5974(HuVecF *pos, HuVecF *out, float range)
{
    M563_COIN *coin;
    int i;
    float dist;

    for (i = 0; i < 30; i++) {
        if (lbl_1_bss_134[i] != NULL) {
            coin = lbl_1_bss_134[i]->data;
            dist = fn_1_6110(pos->x, pos->z, coin->pos.x, coin->pos.z);
            if (dist < range && coin->catchF && fn_1_5A7C(&coin->pos)) {
                out->x = coin->pos.x;
                out->y = coin->pos.y;
                out->z = coin->pos.z;
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL fn_1_5A7C(HuVecF *pos)
{
    HuVecF min = { -650.0f, 240.0f, -450.0f };
    HuVecF max = { 650.0f, 240.0f, 700.0f };

    if (pos->x > min.x && pos->z > min.z && pos->x < max.x && pos->z < max.z) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void fn_1_5B14(int moveF)
{
    M563_PLAYER *work;
    int i;

    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_124[i]->data;
        if (moveF) {
            MgPlayerAttrReset(lbl_1_bss_14[work->playerNo], MGPLAYER_ATTR_COMSTK);
        } else {
            MgPlayerAttrSet(lbl_1_bss_14[work->playerNo], MGPLAYER_ATTR_COMSTK);
        }
    }
}

/* Unreferenced: turn every player halfway toward facing the camera. */
void fn_1_5BC0(void)
{
    M563_PLAYER *work;
    int i;

    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_124[i]->data;
        work->rot.y = fn_1_7290(work->rot.y, 0.0f, 0.5f);
        lbl_1_bss_14[work->playerNo]->actor->rotY = work->rot.y;
    }
}

BOOL fn_1_5D40(void)
{
    int score[4];
    M563_PLAYER *work;
    int i;
    int max;
    BOOL drawF;
    int num;

    max = 0;
    drawF = FALSE;
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_124[i]->data;
        score[i] = work->score;
        if (score[i] > max) {
            max = score[i];
        }
    }
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_124[i]->data;
        if (max == score[i]) {
            lbl_1_bss_50[i] = work->charNo;
        } else {
            lbl_1_bss_50[i] = -1;
        }
    }
    for (i = 0, num = 0; i < 4; i++) {
        if (max == score[i]) {
            num++;
        }
    }
    if (num >= 2) {
        if (max < 10) {
            drawF = TRUE;
        } else {
            drawF = FALSE;
        }
    }
    if (drawF) {
        lbl_1_bss_50[0] = lbl_1_bss_50[1] = lbl_1_bss_50[2] = lbl_1_bss_50[3] = -1;
    }
    MgSeqWinnerSet(lbl_1_bss_50[0], lbl_1_bss_50[1], lbl_1_bss_50[2], lbl_1_bss_50[3]);
    return drawF;
}

void fn_1_5F14(OMOBJ *obj, int motNo, float shift, u32 attr)
{
    M563_PLAYER *work;

    work = obj->data;
    if (work->motNo != motNo) {
        work->motNo = motNo;
        if (shift > 0.0f) {
            CharMotionShiftSet(lbl_1_bss_14[work->playerNo]->charNo, work->motId[motNo], 0.0f, shift, attr);
        } else {
            CharMotionSet(lbl_1_bss_14[work->playerNo]->charNo, work->motId[motNo]);
            Hu3DModelAttrSet(lbl_1_bss_14[work->playerNo]->actor->mdlId, attr);
        }
    }
}

void fn_1_6038(OMOBJ *obj, s16 stepFx)
{
    M563_PLAYER *work;

    work = obj->data;
    if (work->stepFx != stepFx) {
        work->stepFx = stepFx;
        CharModelStepFxSet(lbl_1_bss_14[work->playerNo]->charNo, stepFx);
    }
}

void fn_1_60B4(OMOBJ *obj)
{
    MgActorExec();
}

int fn_1_60D4(int min, int max)
{
    return min + frandmod(max - min);
}

float fn_1_6110(float x1, float z1, float x2, float z2)
{
    float dx;
    float dz;
    float dist;

    dx = x1 - x2;
    dz = z1 - z2;
    dist = sqrtf((dx * dx) + (dz * dz));
    return dist;
}

/* Opening volley: three flowers onto fixed points on each side. */
void fn_1_6280(void)
{
    HuVecF end;
    HuVecF start;
    M563_COIN *coin;
    int side;
    int j;
    int idx;
    int set;
    BOOL waterF;
    float scale;
    float time;

    for (side = 0; side < 4; side++) {
        OMOBJ *obj;

        for (j = 0; j < 3; j++) {
            idx = lbl_1_data_1D4[side][j];
            switch (side) {
                case 0:
                    set = 0;
                    scale = 1.0f;
                    break;
                case 1:
                    set = 1;
                    scale = 1.0f;
                    break;
                case 2:
                    set = 0;
                    scale = -1.0f;
                    break;
                case 3:
                    set = 1;
                    scale = -1.0f;
                    break;
            }
            end.x = scale * lbl_1_data_358[set][idx].x;
            if (75.0f == lbl_1_data_358[set][idx].y) {
                waterF = TRUE;
            } else {
                waterF = FALSE;
            }
            end.y = lbl_1_data_358[set][idx].y - 75.0f;
            end.z = lbl_1_data_358[set][idx].z;
            fn_1_79C8(side, idx, 1);
            start.x = lbl_1_data_244[side].x;
            start.y = lbl_1_data_244[side].y;
            start.z = lbl_1_data_244[side].z;
            lbl_1_bss_98++;
            obj = omAddObjEx(lbl_1_bss_3B0, 101, 1, 0, 1, fn_1_41B0);
            obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M563_COIN), HU_MEMNUM_OVL);
            obj->work[0] = 0;
            coin = obj->data;
            coin->target.x = end.x;
            coin->target.y = end.y;
            coin->target.z = end.z;
            coin->phase = 0;
            coin->side = side;
            coin->posIdx = idx;
            coin->bobTime = 0.0f;
            coin->state = M563_COIN_FALL;
            coin->catchF = FALSE;
            coin->rot.x = coin->rot.y = coin->rot.z = 0.0f;
            coin->pos.x = start.x;
            coin->pos.y = start.y;
            coin->pos.z = start.z;
            coin->endPos.x = end.x;
            coin->endPos.y = end.y;
            coin->endPos.z = end.z;
            coin->waterF = waterF;
            time = 90.0f + 0.23529413f * (frand() & 0xFF);
            coin->vel.x = (coin->endPos.x - coin->pos.x) / time;
            coin->vel.y = (coin->endPos.y - coin->pos.y) / time;
            coin->vel.z = (coin->endPos.z - coin->pos.z) / time;
        }
    }
}

/* Result jingle: repeats every 65 frames once the prize models drop. */
void fn_1_660C(OMOBJ *obj)
{
    if (MgSeqModeGet() <= MGSEQ_MODE_WINNER && lbl_1_bss_4) {
        if (lbl_1_bss_8 != 0) {
            if (lbl_1_bss_8 == 5) {
                HuAudFXPlay(0x8CE);
            } else if (lbl_1_bss_8 % 65 == 0) {
                HuAudFXPlay(0x8CE);
            }
        }
        lbl_1_bss_8++;
    }
}
