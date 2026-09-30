/*
 * m571dll Donkey Kong host block, #included by m571.c right after
 * REL/m563dll/math.c. SKELETON (W1): empty stubs in reference order.
 * Line ranges are into build/mp5-asm/m571dll/asm/REL/m571dll/m571.s.
 *
 * Everything here is shared with m573dll ("KAWASHITE BANANA"). Checked
 * against the reference asm on 2026-09-11:
 *
 *  - .data:0x0..0x1A4 is byte-identical to m573's .data:0x0..0x1A4, so the
 *    objects below are m573.c's (renamed back to address names).
 *  - fn_1_4D3C..fn_1_9350 are instruction-identical (symbol-normalized) to
 *    m573's fn_1_42A8..fn_1_88BC. W2 ports the bodies from m573.c; the
 *    m573 name of each is on its stub.
 *  - .bss:0x35C..0x47C is m573's .bss:0x164..0x284 (same objects, +0x1F8).
 *
 * m573.c spells math.c's helpers with its own names. When porting, rename:
 *
 *   M573Unk3300 -> fn_1_66D4    M573Unk3718    -> fn_1_6AEC
 *   M573Unk3324 -> fn_1_66F8    M573Unk37A4    -> fn_1_6B78
 *   M573Unk33AC -> fn_1_6780    M573Unk3AD8    -> fn_1_6EAC
 *   M573Unk3450 -> fn_1_6824    M573Unk3EBC    -> fn_1_7290
 *   M573Unk34A8 -> fn_1_687C    M573Unk3FC0    -> fn_1_7394
 *   M573Unk35BC -> fn_1_6990    M573Unk402C    -> fn_1_7400
 *   M573RandRange -> fn_1_7458  M573ScreenXLerp -> fn_1_74F4
 *   M573HitCheck  -> fn_1_7494  M573ScreenYLerp -> fn_1_75B8
 *
 * (math.c's names are m563's addresses; m571 has them at fn_1_3D94..
 * fn_1_4C78.) m573.c's M573_PLAYER-typed code stays in m573: nothing here
 * touches a player work.
 */

#include "game/mg/score.h"
#include "game/esprite.h"

/* M573_HOST: the host object's work, 0xB0 bytes (fn_1_7670 is its init). */
typedef struct M571Host_s {
    /* 0x00 */ HU3DMODELID modelId;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ u8 unk10[0x0C];
    /* 0x1C */ HuVecF rot;
    /* 0x28 */ float unk28;
    /* 0x2C */ int motNo;
    /* 0x30 */ int unk30;      /* state; fn_1_5228 switches on it */
    /* 0x34 */ int unk34;
    /* 0x38 */ int unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ float unk40;
    /* 0x44 */ int unk44;
    /* 0x48 */ int unk48;
    /* 0x4C */ int unk4C;
    /* 0x50 */ float unk50;
    /* 0x54 */ HU3DMODELID unk54;
    /* 0x56 */ HU3DMODELID unk56;
    /* 0x58 */ HU3DMODELID unk58;
    /* 0x5A */ u8 unk5A[0x06];
    /* 0x60 */ int unk60;
    /* 0x64 */ float unk64;
    /* 0x68 */ float unk68;
    /* 0x6C */ float unk6C;
    /* 0x70 */ float unk70;
    /* 0x74 */ float unk74;
    /* 0x78 */ u8 unk78[0x04];
    /* 0x7C */ int unk7C;
    /* 0x80 */ HuVecF dest;
    /* 0x8C */ HuVecF from;
    /* 0x98 */ HuVecF step;
    /* 0xA4 */ int unkA4;
    /* 0xA8 */ HU3DMODELID unkA8[2];
    /* 0xAC */ HU3DMODELID unkAC;
    /* 0xAE */ s16 padAE;
} M571_HOST;                       /* 0xB0 */

/* M573_EFF: the 0x18 work of the objects fn_1_8D54 and fn_1_2468 spawn. */
typedef struct M571Eff_s {
    /* 0x00 */ int unk00;
    /* 0x04 */ int unk04;
    /* 0x08 */ int unk08;
    /* 0x0C */ HuVecF pos;
} M571_EFF;                        /* 0x18 */

/* M573_SLOTOBJ: the work of the twenty objects bss_368 holds. */
typedef struct M571SlotObj_s {
    /* 0x00 */ int mode;
    /* 0x04 */ int timer;
    /* 0x08 */ HuVecF pos;
    /* 0x14 */ HuVecF rot;
    /* 0x20 */ HuVecF target;
    /* 0x2C */ HuVecF vel;
    /* 0x38 */ HuVecF screen;
    /* 0x44 */ int no;
} M571_SLOTOBJ;                    /* 0x48 */

static void fn_1_4D3C(OMOBJ *obj, int motNo, float time, int attr);
static void fn_1_4E44(OMOBJ *obj, int motNo, float time, int attr);
static void fn_1_4EC0(OMOBJ *obj, int motNo);
static void fn_1_4F20(OMOBJ *obj);
static void fn_1_50A8(OMOBJ *obj);
static void fn_1_5228(OMOBJ *obj);
static void fn_1_7670(OMOBJ *obj);
static int fn_1_7A78(void);
static void fn_1_7AC8(OMOBJ *obj);
static void fn_1_7DF8(OMOBJ *obj);
static void fn_1_832C(OMOBJ *obj);
static void fn_1_8360(void);
static void fn_1_83C0(int val);
static void fn_1_83D0(int a, int b, int c, int d, int e);
static void fn_1_8478(int no, int val);
static void fn_1_8490(int no);
static void fn_1_8584(OMOBJ *obj);
static void fn_1_8654(OMOBJ *obj);
static void fn_1_8948(OMOBJ *obj);
static void fn_1_8A58(HuVecF *pos, int no);
static void fn_1_8BA8(OMOBJ *obj);
static void fn_1_8D54(HuVecF *pos, int a, int b);
static int fn_1_8E08(void);
static void fn_1_8E5C(void);
static void fn_1_8E70(void);
static void fn_1_8EA0(void);
static int fn_1_8ED0(HuVecF *a, HuVecF *b, float ra, float rb);
static int fn_1_90C8(HuVecF *a, HuVecF *b, float ra, float rb);
static float fn_1_9128(float ax, float az, float bx, float bz);
static int fn_1_9298(int min, int max);
static int fn_1_92D4(HuVecF *pos);
static int fn_1_9350(HuVecF *pos);

/* --- .data:0x0..0x1A4 (m573 names in brackets) --- */

/* [CharIconTbl] each character's face icon; 0x25 is skipped. */
u32 lbl_1_data_0[13] = {
    DATANUM(DATA_mgconst, 0x20), DATANUM(DATA_mgconst, 0x21),
    DATANUM(DATA_mgconst, 0x22), DATANUM(DATA_mgconst, 0x23),
    DATANUM(DATA_mgconst, 0x24), DATANUM(DATA_mgconst, 0x26),
    DATANUM(DATA_mgconst, 0x27), DATANUM(DATA_mgconst, 0x28),
    DATANUM(DATA_mgconst, 0x29), DATANUM(DATA_mgconst, 0x2A),
    DATANUM(DATA_mgconst, 0x2B), DATANUM(DATA_mgconst, 0x2C),
    DATANUM(DATA_mgconst, 0x2D)
};

/* [HostMotData] the host's fifteen joint motions. */
u32 lbl_1_data_34[15] = {
    DATANUM(DATA_m571, 0x08), DATANUM(DATA_m571, 0x09), DATANUM(DATA_m571, 0x0A),
    DATANUM(DATA_m571, 0x0D), DATANUM(DATA_m571, 0x0E), DATANUM(DATA_m571, 0x0F),
    DATANUM(DATA_m571, 0x10), DATANUM(DATA_m571, 0x11), DATANUM(DATA_m571, 0x12),
    DATANUM(DATA_m571, 0x13), DATANUM(DATA_m571, 0x14), DATANUM(DATA_m571, 0x15),
    DATANUM(DATA_m571, 0x16), DATANUM(DATA_m571, 0x0B), DATANUM(DATA_m571, 0x0C)
};

HuVecF lbl_1_data_70 = { 0.0f, 100.0f, -750.0f };                 /* [HostResultPos] */

float lbl_1_data_7C[4][2] = {                                       /* [Unk7CTbl] */
    { 71.0f, 60.0f }, { 191.0f, 60.0f }, { 385.0f, 60.0f }, { 505.0f, 60.0f }
};

HuVecF lbl_1_data_9C[2] = { { -880.0f, 0.0f, -140.0f }, { 880.0f, 0.0f, -140.0f } };   /* [HostSidePos] */
HuVecF lbl_1_data_B4[2] = { { 0.0f, 90.0f, 0.0f }, { 0.0f, 270.0f, 0.0f } };           /* [HostSideRot] */
HuVecF lbl_1_data_CC[2] = { { -700.0f, 0.0f, -140.0f }, { 700.0f, 0.0f, -140.0f } };   /* [SidePos] */

/* [LightPos/LightAim/LightColor] read by m571's own ObjectSetup. */
HuVecF lbl_1_data_E4 = { 0.0f, 10000.0f, 10000.0f };
HuVecF lbl_1_data_F0 = { 0.0f, 0.0f, 0.0f };
u8 lbl_1_data_FC[4] = { 255, 255, 255, 255 };

/* .data:0x100..0x12F are hook-object name literals; 0x130 is fn_1_5228's jump table. */

/* --- .bss:0x35C..0x47C (m573 names in brackets) --- */

/* Declared descending: CodeWarrior emits .bss in reverse declaration order,
 * so this lands ascending at the reference's addresses. */
OMOBJ **lbl_1_bss_478;              /* [HostObjs] group 5 member list */
s32 lbl_1_bss_474;                  /* never read; why dtk sizes bss_470 0x8 */
OMOBJ *lbl_1_bss_470;               /* [Unk278] */
s32 lbl_1_bss_46C;                  /* [Unk274] */
HU3DMOTID lbl_1_bss_44C[16];        /* [MotIds] */
s32 lbl_1_bss_43C[4];               /* [Unk244] */
s32 lbl_1_bss_438;                  /* [Unk240] */
s32 lbl_1_bss_428[4];               /* [Unk230] */
s32 lbl_1_bss_418[4];               /* [Unk220] */
s32 lbl_1_bss_408[4];               /* [Unk210] */
s32 lbl_1_bss_3F8[4];               /* [Unk200] */
float lbl_1_bss_3E8[4];             /* [Unk1F0] */
HUSPRGRPID lbl_1_bss_3E0[4];        /* [ScoreWins] */
s16 lbl_1_bss_3D8[4];               /* [FaceEsp] */
s16 lbl_1_bss_3D0[4];               /* [ItemEsp] */
s16 lbl_1_bss_3C8[4];               /* [CountEsp] */
MGSCORE *lbl_1_bss_3B8[4];          /* [Scores] */
OMOBJ *lbl_1_bss_368[20];           /* [Unk170] M571_SLOTOBJ objects */
HU3DMODELID lbl_1_bss_364;          /* [Model16C] */
s32 lbl_1_bss_360;                  /* [Unk168] */
s32 lbl_1_bss_35C;                  /* [Unk164] stream number */

/* asm 5341-5415, 66 insns. [M573Unk42A8] */
static void fn_1_4D3C(OMOBJ *obj, int motNo, float time, int attr)
{
    M571_HOST *host;

    host = obj->data;
    if(motNo == 8) {
        Hu3DMotionSpeedSet(host->modelId, 2.0f);
    } else {
        Hu3DMotionSpeedSet(host->modelId, 1.0f);
    }
    if(host->motNo != motNo) {
        if(motNo == 2 || motNo == 13) {
            HuAudFXPlay(0x2DB);
        } else if(motNo == 14) {
            HuAudFXPlay(0x2DD);
        }
        host->motNo = motNo;
        Hu3DMotionShiftSet(host->modelId, lbl_1_bss_44C[motNo], 0.0f, time, attr);
        if(motNo == 14) {
            HuAudJinglePlay(0x7A);
        }
        if(motNo == 13) {
            HuAudJinglePlay(0x79);
        }
    }
}

/* asm 5418-5450, 31 insns. [M573Unk43B0] */
static void fn_1_4E44(OMOBJ *obj, int motNo, float time, int attr)
{
    M571_HOST *host;

    host = obj->data;
    host->motNo = motNo;
    Hu3DMotionShiftSet(host->modelId, lbl_1_bss_44C[motNo], 0.0f, time, attr);
}

/* asm 5453-5478, 24 insns. [M573Unk442C] */
static void fn_1_4EC0(OMOBJ *obj, int motNo)
{
    M571_HOST *host;

    host = obj->data;
    host->motNo = motNo;
    Hu3DMotionSet(host->modelId, lbl_1_bss_44C[motNo]);
}

/* asm 5481-5583, 98 insns. [M573Unk448C] */
static void fn_1_4F20(OMOBJ *obj)
{
    M571_HOST *host;

    host = obj->data;
    if(host->unk7C % 3 == 0) {
        Hu3DModelHookObjReset(host->modelId, "a-itemhook-l");
        Hu3DModelHookSet(host->modelId, "a-itemhook-r", host->unk56);
        Hu3DModelAttrReset(host->unk56, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(host->unk58, HU3D_ATTR_DISPOFF);
    } else if(host->unk7C % 3 == 1) {
        Hu3DModelHookObjReset(host->modelId, "a-itemhook-r");
        Hu3DModelHookSet(host->modelId, "a-itemhook-l", host->unk58);
        Hu3DModelAttrReset(host->unk58, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(host->unk58, 0x40000002);
        Hu3DMotionTimeSet(host->unk58, 0.0f);
        Hu3DModelAttrSet(host->unk56, HU3D_ATTR_DISPOFF);
    } else if(host->unk7C % 3 == 2) {
        Hu3DModelHookObjReset(host->modelId, "a-itemhook-r");
        Hu3DModelHookObjReset(host->modelId, "a-itemhook-l");
        Hu3DModelAttrSet(host->unk56, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(host->unk58, HU3D_ATTR_DISPOFF);
    }
}

/* asm 5586-5686, 96 insns. [M573Unk4614] */
static void fn_1_50A8(OMOBJ *obj)
{
    M571_HOST *host;

    host = obj->data;
    if(host->unk7C % 3 == 0) {
        host->rot.y = 90.0f;
        Hu3DModelHookObjReset(host->unk54, "itemhook1");
        Hu3DModelHookSet(host->unk54, "itemhook2", host->modelId);
        host->unk74 = 180.0f;
    } else if(host->unk7C % 3 == 1) {
        host->rot.y = 270.0f;
        Hu3DModelHookObjReset(host->unk54, "itemhook2");
        Hu3DModelHookSet(host->unk54, "itemhook1", host->modelId);
        host->unk74 = 0.0f;
    } else if(host->unk7C % 3 == 2) {
        host->rot.y = 90.0f;
        Hu3DModelHookObjReset(host->unk54, "itemhook1");
        Hu3DModelHookSet(host->unk54, "itemhook2", host->modelId);
        host->unk74 = 180.0f;
    }
}

/* asm 5689-8119, 2322 insns. [M573Unk4794] host state machine, jumptable_1_data_130. */
static void fn_1_5228(OMOBJ *obj)
{
    M571_HOST *host;

    host = obj->data;
    switch(host->unk30) {
    case 1:
        fn_1_4D3C(obj, 2, 8.0f, 0);
        break;

    case 2:
        if(host->unk38 == 0) {
            fn_1_4D3C(obj, 3, 8.0f, 0);
            HuAudFXPlay(0x969);
        } else if(host->unk38 > 5) {
            if(host->unk38 > 30) {
                host->unk30 = 0;
                fn_1_4D3C(obj, 0, 8.0f, 0x40000001);
                Hu3DModelAttrSet(host->modelId, HU3D_ATTR_DISPOFF);
            } else {
                host->pos.y = host->unk40 + 300.0 * sin((M_PI * host->unk3C) / 180.0);
                host->unk3C += 3.6f;
            }
        }
        host->unk38++;
        break;

    case 3:
        host->rot.y = 90.0f;
        host->pos.x = host->pos.y = host->pos.z = 0.0f;
        host->unk7C = 0;
        fn_1_50A8(obj);
        fn_1_4F20(obj);
        fn_1_4D3C(obj, host->unk7C % 3 + 5, 0.0f, 0x40000002);
        Hu3DMotionSpeedSet(host->modelId, 0.0f);
        host->unk68 = -60.0f;
        host->unk64 = 0.0f;
        host->unk6C = -90.0f;
        host->unk70 = 0.0f;
        host->unk74 = 180.0f;
        Hu3DModelRotSet(host->unk54, host->unk70, host->unk74, host->unk64 + host->unk68);
        Hu3DModelAttrReset(host->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(host->unk54, HU3D_ATTR_DISPOFF);
        host->unk30 = 4;
        break;

    case 4:
        host->unk68 = (90.0 * sin((M_PI * host->unk6C) / 180.0)) / 1.5;
        host->unk6C += 1.0f;
        host->unk60++;
        Hu3DModelRotSet(host->unk54, host->unk70, host->unk74, host->unk64 + host->unk68);
        if(host->unk60 > 180) {
            host->unk30 = 5;
            host->unk38 = 0;
        } else {
            if(host->unk60 == 30) {
                Hu3DModelAttrReset(host->modelId, 0x40000002);
                Hu3DMotionSpeedSet(host->modelId, 1.0f);
                if(host->unk7C % 3 == 1) {
                    Hu3DModelAttrReset(host->unk58, 0x40000002);
                    Hu3DModelAttrSet(host->unk58, 0);
                }
            }
            if(host->unk7C == 1 && host->unk60 == 102) {
                HuAudFXPlay(0x96A);
            }
        }
        break;

    case 5:
        if(host->unk38 > 30) {
            host->unk30 = 4;
            host->unk38 = 0;
            host->unk60 = 0;
            host->unk7C++;
            fn_1_50A8(obj);
            fn_1_4F20(obj);
            fn_1_4D3C(obj, host->unk7C % 3 + 5, 0.0f, 0x40000002);
            Hu3DMotionSpeedSet(host->modelId, 0.0f);
            if(host->unk7C >= 3) {
                host->unk30 = 0;
            }
        } else {
            host->unk38++;
        }
        break;

    case 6:
        if(host->unk38 == 0) {
            if(fn_1_7A78() == 0) {
                fn_1_4D3C(obj, 14, 8.0f, 0);
            } else {
                fn_1_4D3C(obj, 13, 8.0f, 0);
            }
        }
        break;

    case 7:
        host->from.x = host->pos.x;
        host->from.y = host->pos.y;
        host->from.z = host->pos.z;
        host->step.x = (host->dest.x - host->from.x) / host->unk44;
        host->step.y = (host->dest.y - host->from.y) / host->unk44;
        host->step.z = (host->dest.z - host->from.z) / host->unk44;
        host->rot.y = 180.0 * (atan2(host->dest.x - host->pos.x, host->dest.z - host->pos.z) / M_PI);
        host->unk30 = 8;
        fn_1_4D3C(obj, 1, 8.0f, 0x40000001);
        break;

    case 8:
        if(host->unk38 > host->unk44) {
            if(host->unk34 != -1) {
                host->unk30 = host->unk34;
                host->unk34 = -1;
                host->unk38 = 0;
            } else {
                host->unk30 = 0;
            }
        } else {
            host->unk38++;
            host->pos.x += host->step.x;
            host->pos.y += host->step.y;
            host->pos.z += host->step.z;
        }
        break;

    case 9:
        host->unk3C = 0.0f;
        host->unk40 = host->pos.y;
        host->unk30 = 10;
        break;

    case 10:
        if(host->unk38 > host->unk48) {
            if(host->unk4C > 0) {
                host->unk30 = 11;
                host->unk38 = 0;
            } else if(host->unk34 != -1) {
                host->unk30 = host->unk34;
                host->unk34 = -1;
                host->unk38 = 0;
            } else {
                host->unk30 = 0;
            }
            fn_1_4D3C(obj, 0, 8.0f, 0x40000001);
        } else {
            fn_1_4D3C(obj, 3, 8.0f, 0);
            host->pos.y = host->unk40 + 100.0 * sin((M_PI * host->unk3C) / 180.0);
            host->pos.x = host->pos.x + (host->unk50 * sin((M_PI * host->rot.y) / 180.0)) / host->unk48;
            host->pos.z = host->pos.z + (host->unk50 * cos((M_PI * host->rot.y) / 180.0)) / host->unk48;
            host->unk38++;
            host->unk3C += 180.0f / host->unk48;
        }
        break;

    case 11:
        if(host->unk38 > host->unk4C) {
            if(host->unk34 != -1) {
                host->unk30 = host->unk34;
                host->unk34 = -1;
                host->unk38 = 0;
            } else {
                host->unk30 = 0;
            }
        } else {
            host->unk38++;
            host->pos.y = host->unk40 + 100.0 * sin((M_PI * (host->unk3C + host->unk38)) / 180.0);
        }
        break;

    case 12:
        fn_1_4D3C(obj, 1, 8.0f, 0x40000001);
        if(host->unk38 > 30) {
            host->unk30 = 7;
            host->dest.x = 180.0f;
            host->dest.y = host->pos.y;
            host->dest.z = -800.0f;
            host->unk44 = 30;
            host->unk34 = 13;
            host->unk38 = 0;
        } else {
            host->unk38++;
            host->rot.y += 3.6666667f;
        }
        break;

    case 13:
        host->unk30 = 9;
        host->unk34 = 15;
        host->unk48 = 40;
        host->unk4C = 0;
        host->unk50 = 200.0f;
        host->unk38 = 0;
        break;

    case 14:
        host->unk30 = 7;
        host->dest.x = 410.0f;
        host->dest.y = 0.0f;
        host->dest.z = -880.0f;
        host->unk44 = 30;
        host->unk34 = 15;
        host->unk38 = 0;
        break;

    case 15:
        fn_1_4D3C(obj, 8, 8.0f, 0x40000001);
        if(host->unk38 > 180) {
            host->rot.x = 0.0f;
            host->unk30 = 9;
            host->unk34 = 16;
            host->unk48 = 45;
            host->unk4C = 15;
            host->unk50 = 100.0f;
            host->unk38 = 0;
        } else {
            host->unk38++;
            host->pos.x += -0.075f;
            host->pos.y += 4.3333335f;
            host->pos.z += -0.575f;
            host->rot.y = 215.0f;
            host->rot.x = 10.0f;
        }
        break;

    case 16:
        host->unk30 = 7;
        host->dest.x = 220.0f;
        host->dest.y = 860.0f;
        host->dest.z = -1050.0f;
        host->unk44 = 30;
        host->unk34 = 17;
        host->unk38 = 0;
        break;

    case 17:
        fn_1_4D3C(obj, 10, 8.0f, 0x40000001);
        if(host->unk38 > 120) {
            host->unk30 = 7;
            host->dest.x = 10.0f;
            host->dest.y = 860.0f;
            host->dest.z = -1070.0f;
            host->unk44 = 30;
            host->unk34 = 18;
            host->unk38 = 0;
        } else {
            host->rot.y = fn_1_7290(host->rot.y, 0.0f, 0.5f);
            host->unk38++;
        }
        break;

    case 18:
        fn_1_4D3C(obj, 8, 8.0f, 0x40000001);
        if(host->unk38 > 180) {
            host->rot.x = 0.0f;
            host->unk30 = 9;
            host->unk34 = 19;
            host->unk48 = 45;
            host->unk4C = 20;
            host->unk50 = 100.0f;
            host->unk38 = 0;
        } else {
            host->unk38++;
            host->pos.y += 3.2777777f;
            host->rot.y = -161.0f;
            host->rot.x = 10.0f;
        }
        break;

    case 19:
        host->unk30 = 7;
        host->dest.x = -180.0f;
        host->dest.y = 1450.0f;
        host->dest.z = -1150.0f;
        host->unk44 = 30;
        host->unk34 = 21;
        host->unk40 = host->pos.y;
        host->unk3C = 0.0f;
        host->unk38 = 0;
        break;

    case 20:
        fn_1_4D3C(obj, 9, 8.0f, 0x40000001);
        if(host->unk38 > 120) {
            host->unk30 = 0;
            host->unk38 = 0;
        } else {
            host->rot.y = fn_1_7290(host->rot.y, 0.0f, 0.5f);
            host->unk38++;
        }
        break;

    case 21:
        if(host->unk38 > 60.0f) {
            host->unk30 = 22;
            fn_1_4D3C(obj, 4, 8.0f, 0);
            host->unk38 = 0;
        } else {
            fn_1_4D3C(obj, 3, 8.0f, 0);
            host->pos.y = host->unk40 + 450.0 * sin((M_PI * host->unk3C) / 180.0);
            host->pos.x = host->pos.x + (200.0 * sin((M_PI * host->rot.y) / 180.0)) / 90.0;
            host->pos.z = host->pos.z + (200.0 * cos((M_PI * host->rot.y) / 180.0)) / 90.0;
            host->unk38++;
            host->unk3C += 2.0f;
        }
        break;

    case 22:
        host->unk38++;
        if(host->unk38 > 30) {
            fn_1_4D3C(obj, 9, 8.0f, 0x40000001);
        }
        host->rot.y = fn_1_7290(host->rot.y, 0.0f, 0.5f);
        break;

    case 24:
        if(host->unk38 > 40) {
            host->unk38 = 0;
            host->unk30 = 25;
        } else {
            host->unk38++;
        }
        break;

    case 25:
        host->pos.x = lbl_1_data_9C[host->unkA4].x;
        host->pos.y = lbl_1_data_9C[host->unkA4].y;
        host->pos.z = lbl_1_data_9C[host->unkA4].z;
        host->rot.x = lbl_1_data_B4[host->unkA4].x;
        host->rot.y = lbl_1_data_B4[host->unkA4].y;
        host->rot.z = lbl_1_data_B4[host->unkA4].z;
        Hu3DModelAttrReset(host->modelId, HU3D_ATTR_DISPOFF);
        host->unk30 = 26;
        fn_1_4E44(obj, 1, 8.0f, 0x40000001);
        Hu3DModelAttrReset(host->unkA8[host->unkA4], 0x40000002);
        Hu3DMotionTimeSet(host->unkA8[host->unkA4], 0.0f);
        if(host->unkA4 == 0) {
            HuAudFXPlay(0x978);
        } else if(host->unkA4 == 1) {
            HuAudFXPlay(0x979);
        }
        break;

    case 26:
        if(host->unkA4 % 2 == 0) {
            host->pos.x += 2.0f;
        } else {
            host->pos.x -= 2.0f;
        }
        if(host->unk38 > 100) {
            host->unk38 = 0;
            host->unk30 = 28;
            if(host->unkA4 % 2 == 0) {
                fn_1_4D3C(obj, 11, 8.0f, 0);
                Hu3DModelHookSet(host->modelId, "a-itemhook-l", host->unkAC);
                Hu3DModelAttrReset(host->unkAC, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(host->unkAC, 0x40000002);
            } else {
                fn_1_4D3C(obj, 12, 8.0f, 0);
            }
        } else {
            host->unk38++;
        }
        break;

    case 27:
        if(host->unkA4 % 2 == 0) {
            host->pos.x -= 3.3333333f;
        } else {
            host->pos.x += 3.3333333f;
        }
        if(host->unk38 > 60) {
            host->unk38 = 0;
            host->unk30 = 24;
            host->unkA4++;
            if(host->unkA4 >= 2) {
                host->unkA4 = 0;
                fn_1_4E44(obj, 0, 0.0f, 0);
                host->unk30 = 23;
            }
        } else {
            host->unk38++;
        }
        break;

    case 28:
        if(host->unk38 > 112) {
            host->unk38 = 0;
            host->unk30 = 27;
            fn_1_4E44(obj, 1, 8.0f, 0);
            Hu3DModelHookObjReset(host->modelId, "a-itemhook-l");
            Hu3DModelAttrSet(host->unkAC, HU3D_ATTR_DISPOFF);
        } else {
            host->unk38++;
        }
        if(host->unkA4 == 0 && host->unk38 == 52) {
            HuAudFXPlayPan(0x96A, 0x20);
        }
        break;
    }
    Hu3DModelPosSet(host->modelId, host->pos.x, host->pos.y, host->pos.z);
    Hu3DModelRotSet(host->modelId, host->rot.x, host->rot.y, host->rot.z);
}

/* asm 8122-8389, 258 insns. [M573HostInit] */
static void fn_1_7670(OMOBJ *obj)
{
    M571_HOST *host;
    int i;

    host = obj->data;
    host->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x07), HU_MEMNUM_OVL, HEAP_MODEL));
    if(obj->work[0] == 0) {
        host->unk54 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x17), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(host->unk54, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(host->unk54, 0.0f, 1050.0f, 300.0f);
        Hu3DModelRotSet(host->unk54, 0.0f, 180.0f, 0.0f);
        Hu3DMotionClusterSpeedSet(host->unk54, 0, 1.0f);
        Hu3DModelClusterAttrSet(host->unk54, 0, 0xC0000001);
        host->unk56 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x1D), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(host->unk56, HU3D_ATTR_DISPOFF);
        host->unk58 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x1B), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(host->unk58, 0x40000002);
        Hu3DModelAttrSet(host->unk58, HU3D_ATTR_DISPOFF);
    } else if(obj->work[0] == 1) {
    } else if(obj->work[0] == 2) {
        for(i=0; i<2; i++) {
            host->unkA8[i] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m573, 0x02), HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelPosSet(host->unkA8[i], lbl_1_data_CC[i].x, lbl_1_data_CC[i].y, lbl_1_data_CC[i].z);
            Hu3DModelAttrSet(host->unkA8[i], 0x40000002);
            if(i == 0) {
                Hu3DModelScaleSet(host->unkA8[i], 1.0f, 1.0f, 1.0f);
            } else {
                Hu3DModelScaleSet(host->unkA8[i], -1.0f, 1.0f, 1.0f);
            }
        }
        host->unkAC = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x1C), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(host->unkAC, 0x40000002);
        Hu3DModelAttrSet(host->unkAC, HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<15; i++) {
        lbl_1_bss_44C[i] = Hu3DJointMotion(host->modelId, HuDataSelHeapReadNum(lbl_1_data_34[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    host->motNo = 0;
    Hu3DMotionSet(host->modelId, lbl_1_bss_44C[0]);
    Hu3DModelAttrSet(host->modelId, 0x40000001);
    Hu3DModelShadowSet(host->modelId);
    host->pos.x = lbl_1_data_70.x;
    host->pos.y = lbl_1_data_70.y;
    host->pos.z = lbl_1_data_70.z;
    host->rot.x = host->rot.y = host->rot.z = 0.0f;
    host->unk30 = 0;
    host->unk34 = -1;
    host->unk38 = 0;
    host->unk28 = 0.0f;
    host->unk60 = 0;
    host->unk7C = 0;
    host->unk40 = host->pos.y;
    host->unk3C = 0.0f;
    host->unkA4 = 0;
    obj->objFunc = fn_1_5228;
}

/* asm 8392-8415, 20 insns. [M573Unk6FE4] */
static int fn_1_7A78(void)
{
    int i;
    int total;

    total = 0;
    for(i=0; i<4; i++) {
        total += lbl_1_bss_428[i];
    }
    return total;
}

/* asm 8418-8632, 204 insns. [M573Unk7034] score windows, per frame. */
static void fn_1_7AC8(OMOBJ *obj)
{
    int i;

    if(MgSeqModeGet() < 5) {
        return;
    }
    for(i=0; i<4; i++) {
        MgScoreWinDispSet(lbl_1_bss_3E0[i], TRUE);
        espDispOn(lbl_1_bss_3D8[i]);
        espDispOn(lbl_1_bss_3D0[i]);
        espDispOn(lbl_1_bss_3C8[i]);
        MgScoreDispOn(lbl_1_bss_3B8[i]);
        if(lbl_1_bss_428[i] > 99) {
            MgScoreValueSet(lbl_1_bss_3B8[i], 99);
        } else {
            MgScoreValueSet(lbl_1_bss_3B8[i], lbl_1_bss_428[i]);
        }
        if(lbl_1_bss_408[i] != 0) {
            if(lbl_1_bss_418[i] > 12) {
                lbl_1_bss_408[i] = 0;
                lbl_1_bss_418[i] = 0;
                lbl_1_bss_3E8[i] = 1.0f;
                MgScoreDigitScaleSet(lbl_1_bss_3B8[i], lbl_1_bss_3E8[i], lbl_1_bss_3E8[i]);
            } else {
                if(lbl_1_bss_418[i] < 4) {
                    if((lbl_1_bss_3E8[i] += 0.2f) >= 1.8f) {
                        lbl_1_bss_3E8[i] = 1.8f;
                    }
                } else {
                    if((lbl_1_bss_3E8[i] -= 0.1f) <= 1.0f) {
                        lbl_1_bss_3E8[i] = 1.0f;
                    }
                }
                lbl_1_bss_418[i]++;
                MgScoreDigitScaleSet(lbl_1_bss_3B8[i], lbl_1_bss_3E8[i], lbl_1_bss_3E8[i]);
            }
        }
    }
}

/* asm 8635-8974, 333 insns. [M573Unk7364] score windows, init. */
static void fn_1_7DF8(OMOBJ *obj)
{
    int i;

    for(i=0; i<4; i++) {
        lbl_1_bss_3E0[i] = MgScoreWinCreate(112, 40);
        MgScoreWinTPLvlSet(lbl_1_bss_3E0[i], 0.85f);
        MgScoreWinPosSet(lbl_1_bss_3E0[i], lbl_1_data_7C[i][0], lbl_1_data_7C[i][1]);
        MgScoreWinDispSet(lbl_1_bss_3E0[i], FALSE);

        lbl_1_bss_3D8[i] = espEntry(lbl_1_data_0[lbl_1_bss_43C[i]], 0x63, 0);
        espDispOff(lbl_1_bss_3D8[i]);
        espDrawNoSet(lbl_1_bss_3D8[i], 0);
        espPosSet(lbl_1_bss_3D8[i], lbl_1_data_7C[i][0] - 38.0f, lbl_1_data_7C[i][1]);
        espAttrSet(lbl_1_bss_3D8[i], 1);

        if(lbl_1_bss_438 == 0) {
            lbl_1_bss_3D0[i] = espEntry(DATANUM(DATA_m571, 0x1E), 0x63, 0);
        } else if(lbl_1_bss_438 == 1) {
            lbl_1_bss_3D0[i] = espEntry(DATANUM(DATA_m572, 0x14), 0x63, 0);
        } else {
            lbl_1_bss_3D0[i] = espEntry(DATANUM(DATA_m573, 0x06), 0x63, 0);
        }
        espDispOff(lbl_1_bss_3D0[i]);
        espDrawNoSet(lbl_1_bss_3D0[i], 0);
        espPosSet(lbl_1_bss_3D0[i], lbl_1_data_7C[i][0] - 15.0f, lbl_1_data_7C[i][1]);
        espAttrSet(lbl_1_bss_3D0[i], 1);

        lbl_1_bss_3C8[i] = espEntry(DATANUM(DATA_mgconst, 0x30), 0x63, 0xF);
        espDispOff(lbl_1_bss_3C8[i]);
        espDrawNoSet(lbl_1_bss_3C8[i], 0);
        espPosSet(lbl_1_bss_3C8[i], 4.0f + lbl_1_data_7C[i][0], lbl_1_data_7C[i][1]);
        espAttrSet(lbl_1_bss_3C8[i], 1);

        lbl_1_bss_3B8[i] = MgScoreCreate(DATANUM(DATA_mgconst, 0x31), -1, TRUE);
        MgScoreValueSet(lbl_1_bss_3B8[i], 0);
        MgScorePosSet(lbl_1_bss_3B8[i], 22.0f + lbl_1_data_7C[i][0], lbl_1_data_7C[i][1]);
        MgScoreMaxDigitSet(lbl_1_bss_3B8[i], 2);
        MgScoreDispOff(lbl_1_bss_3B8[i]);
        MgScorePriSet(lbl_1_bss_3B8[i], 0x63);

        lbl_1_bss_408[i] = 0;
        lbl_1_bss_418[i] = 0;
        lbl_1_bss_3F8[i] = 0;
        lbl_1_bss_3E8[i] = 1.0f;
    }
    obj->objFunc = fn_1_7AC8;
}

/* asm 8977-8992, 13 insns. [M573Unk7898] */
static void fn_1_832C(OMOBJ *obj)
{
    if(lbl_1_bss_46C != 0) {
        MgActorExec();
    }
}

/* asm 8995-9020, 24 insns. [M573Unk78CC] */
static void fn_1_8360(void)
{
    lbl_1_bss_46C = 1;
    lbl_1_bss_470 = omAddObjEx(lbl_1_bss_680, 100, 0, 0, -1, fn_1_832C);
}

/* asm 9023-9028, 4 insns. [M573Unk792C] */
static void fn_1_83C0(int val)
{
    lbl_1_bss_46C = val;
}

/* asm 9031-9074, 42 insns. [M573Unk793C] */
static void fn_1_83D0(int a, int b, int c, int d, int e)
{
    lbl_1_bss_43C[0] = a;
    lbl_1_bss_43C[1] = b;
    lbl_1_bss_43C[2] = c;
    lbl_1_bss_43C[3] = d;
    lbl_1_bss_438 = e;
    omAddObjEx(lbl_1_bss_680, 0x65, 0, 0, -1, fn_1_7DF8);
}

/* asm 9077-9084, 6 insns. [M573Unk79E4] */
static void fn_1_8478(int no, int val)
{
    lbl_1_bss_428[no] = val;
}

/* asm 9087-9154, 61 insns. [M573Unk79FC] */
static void fn_1_8490(int no)
{
    int i;

    if(no == 0) {
        lbl_1_bss_364 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x1A), HU_MEMNUM_OVL, HEAP_MODEL));
    } else if(no == 1) {
        lbl_1_bss_364 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m572, 0x11), HU_MEMNUM_OVL, HEAP_MODEL));
    } else {
        lbl_1_bss_364 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m573, 0x03), HU_MEMNUM_OVL, HEAP_MODEL));
    }
    Hu3DModelAttrSet(lbl_1_bss_364, HU3D_ATTR_DISPOFF);
    for(i=0; i<20; i++) {
        lbl_1_bss_368[i] = NULL;
    }
}

/* asm 9157-9214, 52 insns. [M573Unk7AF0] */
static void fn_1_8584(OMOBJ *obj)
{
    M571_SLOTOBJ *work;
    int i;

    work = obj->data;
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelKill(obj->mdlId[0]);
    lbl_1_bss_360--;
    for(i=0; i<20; i++) {
        if(obj == lbl_1_bss_368[i]) {
            lbl_1_bss_368[i] = NULL;
            break;
        }
    }
    omDelObjEx(lbl_1_bss_680, obj);
}

/* asm 9217-9413, 189 insns. [M573Unk7BC0] */
static void fn_1_8654(OMOBJ *obj)
{
    M571_SLOTOBJ *work;
    M571_SLOTOBJ *dead;
    int i;

    work = obj->data;
    switch(work->mode) {
    case 0:
        Hu3D2Dto3D(&work->screen, 1, &work->target);
        work->vel.x = (work->target.x - work->pos.x) / (30.0f - (float)work->timer);
        work->vel.y = (work->target.y - work->pos.y) / (30.0f - (float)work->timer);
        work->vel.z = (work->target.z - work->pos.z) / (30.0f - (float)work->timer);
        work->pos.x += work->vel.x;
        work->pos.y += work->vel.y;
        work->pos.z += work->vel.z;
        work->rot.y += 10.0f;
        work->timer++;
        if((float)work->timer > 30.0f) {
            work->pos.y = work->target.y;
            work->pos.y = work->target.y;
            work->pos.y = work->target.y;
            dead = obj->data;
            Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelKill(obj->mdlId[0]);
            lbl_1_bss_360--;
            for(i=0; i<20; i++) {
                if(obj == lbl_1_bss_368[i]) {
                    lbl_1_bss_368[i] = NULL;
                    break;
                }
            }
            omDelObjEx(lbl_1_bss_680, obj);
            lbl_1_bss_428[work->no]++;
            lbl_1_bss_408[work->no] = 1;
            HuAudFXPlay(0x96D);
        }
        break;
    }
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
}

/* asm 9416-9489, 68 insns. [M573Unk7EB4] */
static void fn_1_8948(OMOBJ *obj)
{
    M571_SLOTOBJ *work;
    int i;

    work = obj->data;
    obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_364);
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    for(i=0; i<20; i++) {
        if(NULL == lbl_1_bss_368[i]) {
            lbl_1_bss_368[i] = obj;
            break;
        }
    }
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    obj->objFunc = fn_1_8654;
}

/* asm 9492-9577, 84 insns. [M573Unk7FC4] */
static void fn_1_8A58(HuVecF *pos, int no)
{
    OMOBJ *obj;
    M571_SLOTOBJ *work;

    lbl_1_bss_360++;
    obj = omAddObjEx(lbl_1_bss_680, 0x66, 1, 0, -1, fn_1_8948);
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M571_SLOTOBJ), HU_MEMNUM_OVL);
    work = obj->data;
    work->mode = 0;
    work->timer = 0;
    work->screen.x = lbl_1_data_7C[no][0];
    work->screen.y = 20.0f + lbl_1_data_7C[no][1];
    work->screen.z = 1500.0f;
    work->rot.x = work->rot.y = work->rot.z = 0.0f;
    work->pos.x = pos->x;
    work->pos.y = pos->y;
    work->pos.z = pos->z;
    work->vel.x = work->target.y = work->vel.z = 0.0f;
    work->no = no;
}

/* asm 9580-9689, 107 insns. [M573Unk8114] */
static void fn_1_8BA8(OMOBJ *obj)
{
    M571_EFF *eff;
    OMOBJ *obj2;
    M571_SLOTOBJ *work;
    int no;

    eff = obj->data;
    if(eff->unk04 % 15 == 0) {
        no = eff->unk08;
        lbl_1_bss_360++;
        obj2 = omAddObjEx(lbl_1_bss_680, 0x66, 1, 0, -1, fn_1_8948);
        obj2->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M571_SLOTOBJ), HU_MEMNUM_OVL);
        work = obj2->data;
        work->mode = 0;
        work->timer = 0;
        work->screen.x = lbl_1_data_7C[no][0];
        work->screen.y = 20.0f + lbl_1_data_7C[no][1];
        work->screen.z = 1500.0f;
        work->rot.x = work->rot.y = work->rot.z = 0.0f;
        work->pos.x = eff->pos.x;
        work->pos.y = eff->pos.y;
        work->pos.z = eff->pos.z;
        work->vel.x = work->target.y = work->vel.z = 0.0f;
        work->no = no;
        eff->unk00--;
        if(eff->unk00 <= 0) {
            omDelObjEx(lbl_1_bss_680, obj);
        }
    }
    eff->unk04++;
}

/* asm 9692-9738, 45 insns. [M573Unk82C0] */
static void fn_1_8D54(HuVecF *pos, int a, int b)
{
    OMOBJ *obj;
    M571_EFF *eff;

    obj = omAddObjEx(lbl_1_bss_680, 0x66, 0, 0, -1, fn_1_8BA8);
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M571_EFF), HU_MEMNUM_OVL);
    eff = obj->data;
    eff->pos.x = pos->x;
    eff->pos.y = pos->y;
    eff->pos.z = pos->z;
    eff->unk08 = a;
    eff->unk00 = b;
    eff->unk04 = 0;
}

/* asm 9741-9767, 21 insns. [M573Unk8374] */
static int fn_1_8E08(void)
{
    int i;

    for(i=0; i<20; i++) {
        if(lbl_1_bss_368[i] != NULL) {
            return 1;
        }
    }
    return 1;
}

/* asm 9770-9776, 5 insns. [M573Unk83C8] */
static void fn_1_8E5C(void)
{
    lbl_1_bss_35C = -1;
}

/* asm 9779-9792, 12 insns. [M573Unk83DC] */
static void fn_1_8E70(void)
{
    lbl_1_bss_35C = HuAudSStreamPlay(0x3D);
}

/* asm 9795-9808, 12 insns. [M573Unk840C] */
static void fn_1_8EA0(void)
{
    HuAudSStreamFadeOut(lbl_1_bss_35C, 100);
}

/* asm 9811-9942, 126 insns. [M573Unk843C] */
static int fn_1_8ED0(HuVecF *a, HuVecF *b, float ra, float rb)
{
    float dx;
    float dy;
    float dz;
    float sum;
    float dist;

    dx = a->x - b->x;
    dy = a->y - b->y;
    dz = a->z - b->z;
    dist = HuMagPoint3D(dx, dy, dz);
    sum = ra + rb;
    if(sum > dist) {
        return 1;
    }
    return 0;
}

/* asm 9945-9972, 24 insns. [M573HitCheck2] */
static int fn_1_90C8(HuVecF *a, HuVecF *b, float ra, float rb)
{
    if(((b->x - a->x) * (b->x - a->x)) + ((b->z - a->z) * (b->z - a->z)) < ((ra + rb) * (ra + rb))) {
        return 1;
    }
    return 0;
}

/* asm 9975-10070, 92 insns. [M573Dist2D] */
static float fn_1_9128(float ax, float az, float bx, float bz)
{
    float dx;
    float dz;
    float d;

    dx = ax - bx;
    dz = az - bz;
    d = HuMagPoint2D(dx, dz);
    return d;
}

/* asm 10073-10089, 15 insns. [M573RandRange2] */
static int fn_1_9298(int min, int max)
{
    return min + frandmod(max - min);
}

/* asm 10092-10124, 31 insns. [M573PanGet] */
static int fn_1_92D4(HuVecF *pos)
{
    HuVecF scr;
    int pan;

    Hu3D3Dto2D(pos, 1, &scr);
    pan = 32.0f + 64.0f * (scr.x / 576.0f);
    return pan;
}

/* asm 10127-10159, 31 insns. [M573VolGet] */
static int fn_1_9350(HuVecF *pos)
{
    HuVecF scr;
    int vol;

    Hu3D3Dto2D(pos, 1, &scr);
    vol = 96.0f + 31.0f * (scr.y / 480.0f);
    return vol;
}
