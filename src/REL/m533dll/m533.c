/*
 * m533dll -- a 2-vs-2 rowing race (MG_TYPE_2VS2, overlay #47).
 *
 * Each team shares a boat: the front player rows with L+R, the back player
 * rests, Y swaps seats, and the first boat past the goal wins. No upstream
 * names or source exist, so functions keep their reference addresses and were
 * written from the reference assembly (see NOTES.md). Keep them in reference
 * order: CodeWarrior's auto-inlining depends on definition order. Line ranges
 * are into build/mp5-asm/m533dll/asm/REL/m533dll/m533.s.
 *
 * Shape: seqman (MgSeqCreate, lbl_1_data_4C8) + own OMOBJ groups. ObjectSetup
 * makes five groups and allocates their works: group 0 players (M533_PLAYER,
 * lbl_1_bss_AC), 1 (M533_WORK2, bss_A8), 2 (M533_WORK3, bss_A4),
 * 4 (M533_WORK4, bss_A0), 5 (M533_WORK5, bss_9C). The helper block at
 * fn_1_5580..fn_1_6464 is REL/m563dll/math.c, included first (see
 * REL/m533Dll.h for the address map); its .bss (model cache, camera lerp
 * state, list head, music number) is math.c's.
 *
 * Several functions copy function-local initializers from .rodata
 * (ObjectSetup's int[2] { -1, -1 } at 0x54 and others); write those as
 * locals. The .data strings are literals where they are used.
 *
 * _prolog and _epilog are not reproduced.
 */

#include "REL/m563dll/math.c"

#include "REL/m533Dll.h"

#include "game/charman.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mg/seqman.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/wipe.h"

/* --- .data --- */

HuVecF lbl_1_data_0 = { 13000.0f, 10000.0f, 0.0f };   /* light position */
HuVecF lbl_1_data_C = { 0.0f, 0.0f, 0.0f };           /* light target */
GXColor lbl_1_data_18 = { 255, 255, 255, 255 };
s32 lbl_1_data_1C = -1;

/* Character motions. */
u32 lbl_1_data_20[10] = {
    0x008C0000, 0x008C0006, 0x008C0031, 0x008C004C, 0x008C0001, 0x008C0002, 0x008C0051, 0x008C004B, 0x008C0032, 0x008C0032
};

u32 lbl_1_data_48[2] = { 0x005B0011, 0x005B0012 };

float lbl_1_data_50[13] = { 1.0f, 1.0f, 2.0f, 1.0f, 1.5f, 2.0f, 1.3f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };

u32 lbl_1_data_84[9] = {
    0x005B0000, 0x005B0001, 0x005B0002, 0x005B0003, 0x005B0004, 0x005B0005, 0x005B000A, 0x005B000B, 0x005B0009
};

HuVecF lbl_1_data_A8[4] = {
    { 4800.0f, -850.0f, 550.0f }, { 4800.0f, -850.0f, 550.0f }, { 5100.0f, -850.0f, 550.0f }, { 5100.0f, -850.0f, 550.0f },
};

HuVecF lbl_1_data_D8[4] = {
    { 11920.0f, -850.0f, 550.0f }, { 11920.0f, -850.0f, 550.0f }, { 12220.0f, -850.0f, 550.0f }, { 12220.0f, -850.0f, 550.0f },
};

M533_SPAWN lbl_1_data_108[24] = {
    { { 7500.0f, 100.0f, -150.0f }, 0, -10.0f },
    { { 7500.0f, 100.0f, -150.0f }, 0, -10.0f },
    { { 7500.0f, -50.0f, -200.0f }, 1, -15.0f },
    { { 7500.0f, -50.0f, -200.0f }, 1, -15.0f },
    { { 7500.0f, -200.0f, -250.0f }, 2, -12.0f },
    { { 7500.0f, -200.0f, -250.0f }, 2, -12.0f },
    { { 7700.0f, 125.0f, -200.0f }, 2, -12.0f },
    { { 7700.0f, 125.0f, -200.0f }, 2, -12.0f },
    { { 7700.0f, -50.0f, -250.0f }, 0, -8.5f },
    { { 7700.0f, -50.0f, -250.0f }, 0, -8.5f },
    { { 7700.0f, -180.0f, -150.0f }, 1, -10.0f },
    { { 7700.0f, -180.0f, -150.0f }, 1, -10.0f },
    { { -1000.0f, 100.0f, -250.0f }, 0, -10.0f },
    { { -1000.0f, 100.0f, -250.0f }, 0, -10.0f },
    { { -1000.0f, 100.0f, -250.0f }, 1, -12.5f },
    { { -1000.0f, 100.0f, -250.0f }, 1, -12.5f },
    { { -1000.0f, 100.0f, -250.0f }, 2, -15.0f },
    { { -1000.0f, 100.0f, -250.0f }, 2, -15.0f },
    { { -1000.0f, 100.0f, -250.0f }, 0, -10.0f },
    { { -1000.0f, 100.0f, -250.0f }, 0, -10.0f },
    { { -1000.0f, 100.0f, -250.0f }, 1, -12.5f },
    { { -1000.0f, 100.0f, -250.0f }, 1, -12.5f },
    { { -1000.0f, 100.0f, -250.0f }, 2, -15.0f },
    { { -1000.0f, 100.0f, -250.0f }, 2, -15.0f },
};

M533_SPAWN lbl_1_data_2E8[24] = {
    { { 13370.0f, 212.5f, -250.0f }, -1, -10.0f },
    { { 13370.0f, 212.5f, -250.0f }, -1, -10.0f },
    { { 13370.0f, 37.5f, -250.0f }, -1, -8.0f },
    { { 13370.0f, 37.5f, -250.0f }, -1, -8.0f },
    { { 13670.0f, 300.0f, -250.0f }, -1, -8.0f },
    { { 13670.0f, 300.0f, -250.0f }, -1, -8.0f },
    { { 13690.0f, 125.0f, -250.0f }, -1, -11.0f },
    { { 13690.0f, 125.0f, -250.0f }, -1, -11.0f },
    { { 13670.0f, -50.0f, -250.0f }, -1, -9.5f },
    { { 13670.0f, -50.0f, -250.0f }, -1, -9.5f },
    { { 13970.0f, 212.5f, -250.0f }, -1, -8.5f },
    { { 13970.0f, 212.5f, -250.0f }, -1, -8.5f },
    { { 14020.0f, 37.5f, -250.0f }, -1, -12.0f },
    { { 14020.0f, 37.5f, -250.0f }, -1, -12.0f },
    { { 14270.0f, 400.0f, -250.0f }, -1, -10.0f },
    { { 14270.0f, 400.0f, -250.0f }, -1, -10.0f },
    { { 14310.0f, 125.0f, -250.0f }, -1, -11.0f },
    { { 14310.0f, 125.0f, -250.0f }, -1, -11.0f },
    { { 14420.0f, -100.0f, -250.0f }, -1, -7.5f },
    { { 14420.0f, -100.0f, -250.0f }, -1, -7.5f },
    { { 14570.0f, 212.5f, -250.0f }, -1, -10.5f },
    { { 14570.0f, 212.5f, -250.0f }, -1, -10.5f },
    { { 14620.0f, 37.5f, -250.0f }, -1, -12.0f },
    { { 14620.0f, 37.5f, -250.0f }, -1, -12.0f },
};

MGSEQ_PARAM lbl_1_data_4C8 = {
    300, MGSEQ_TIMER_TOP,
    fn_1_2D4C,
    fn_1_3424,
    NULL,
    fn_1_3890,
    fn_1_3950,
    fn_1_3D50,
    fn_1_4080,
    NULL,
    NULL
};

HuVecF lbl_1_data_4F0 = { 0.0f, 300.0f, 0.0f };
HuVecF lbl_1_data_4FC = { 1500.0f, -100.0f, 0.0f };

OMCAMERAVIEW lbl_1_data_508 = { { 0.5f, 500.0f, 0.0f }, { -2.0f, 0.0f, 0.0f }, 4100.0f };
OMCAMERAVIEW lbl_1_data_524 = { { 1500.0f, 0.0f, 0.0f }, { -6.0f, 0.0f, 0.0f }, 2700.0f };

/* CPU press intervals per difficulty: { min, max } for stamina 80-100, 60-79
 * and below. fn_1_6A8 gives a human difNo 4 and still calls fn_1_1E3C, which
 * reads row 4 past the end of this table: the bytes of lbl_1_data_5A0 and the
 * first float of lbl_1_data_5B4. Only fn_1_1CD0 (CPU players) reads the
 * result. The host build spells that row out so the read stays in bounds and
 * yields the same values. */
s32 lbl_1_data_540[4][6] = {
    { 16, 21, 21, 26, 26, 30 }, { 13, 18, 18, 23, 23, 28 }, { 10, 15, 15, 20, 21, 25 }, { 7, 12, 12, 17, 17, 22 },
};

float lbl_1_data_5A0[5] = { 3.0f, 2.5f, 2.0f, 1.5f, 1.5f };
float lbl_1_data_5B4[5] = { 10.0f, 15.0f, 20.0f, 25.0f, 25.0f };

/* --- .bss (math.c owns bss_B4..bss_2AC and bss_2BC) --- */

s32 lbl_1_bss_0;
s32 lbl_1_bss_4;
s32 lbl_1_bss_8;
s32 lbl_1_bss_C;
HU3DMODELID lbl_1_bss_10[10];
float lbl_1_bss_24;
s32 lbl_1_bss_28;
u32 lbl_1_bss_2C;
u32 lbl_1_bss_30;
s16 lbl_1_bss_34[4];
s16 lbl_1_bss_3C;                 /* esp sprites */
s16 lbl_1_bss_3E;
s16 lbl_1_bss_40;
s16 lbl_1_bss_42;
float lbl_1_bss_44[2];
HU3DMODELID lbl_1_bss_4C[2];
HU3DMODELID lbl_1_bss_50[2];
s16 lbl_1_bss_54[24];
HU3DMODELID lbl_1_bss_84[2];
HU3DMODELID lbl_1_bss_88[4];
HU3DMODELID lbl_1_bss_90[4];
OMOBJ *lbl_1_bss_98;              /* omOutViewMulti */
OMOBJ **lbl_1_bss_9C;             /* group 5 */
OMOBJ **lbl_1_bss_A0;             /* group 4 */
OMOBJ **lbl_1_bss_A4;             /* group 2 */
OMOBJ **lbl_1_bss_A8;             /* group 1 */
OMOBJ **lbl_1_bss_AC;             /* group 0: players */
OMOBJ *lbl_1_bss_B0;
OMOBJMAN *lbl_1_bss_2B8;

/* asm 61-461, 386 insns. */
void ObjectSetup(void)
{
    OMOBJ *obj;
    s32 i;
    s32 grp;
    s32 unused = 0;
    s32 side[2] = { -1, -1 };

    OSReport("******* M533 ObjectSetup *********\n");
    lbl_1_bss_2B8 = omInitObjMan(200, 0x2000);
    omGameSysInit(lbl_1_bss_2B8);
    mathMusicNo = -1;
    omCameraViewSetMulti(3, &lbl_1_data_508);
    Hu3DCameraCreate(3);
    fn_1_46A4(0.0f);
    lbl_1_bss_98 = omAddObjEx(lbl_1_bss_2B8, 0x7FDA, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_98->work[0] = 2;
    lbl_1_bss_42 = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DGLightPosAimSetV(lbl_1_bss_42, &lbl_1_data_0, &lbl_1_data_C);
    Hu3DGLightStaticSet(lbl_1_bss_42, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_42);
    Hu3DGLightColorSet(lbl_1_bss_42, lbl_1_data_18.r, lbl_1_data_18.g, lbl_1_data_18.b, lbl_1_data_18.a);
    omMakeGroupEx(lbl_1_bss_2B8, 0, 4);
    lbl_1_bss_AC = omGetGroupMemberListEx(lbl_1_bss_2B8, 0);
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(lbl_1_bss_2B8, 100, 1, 10, 0, fn_1_6A8);
        lbl_1_bss_AC[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M533_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
        grp = GwPlayerConf[i].grp;
        obj->work[1] = grp;
        if (side[grp] == -1) {
            side[grp] = frandmod(2);
            obj->work[2] = side[grp];
        } else if (side[grp] == 0) {
            obj->work[2] = 1;
        } else {
            obj->work[2] = 0;
        }
    }
    omMakeGroupEx(lbl_1_bss_2B8, 1, 4);
    lbl_1_bss_A8 = omGetGroupMemberListEx(lbl_1_bss_2B8, 1);
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(lbl_1_bss_2B8, 101, 1, 1, 1, fn_1_165C);
        lbl_1_bss_A8[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M533_WORK2), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    omMakeGroupEx(lbl_1_bss_2B8, 2, 2);
    lbl_1_bss_A4 = omGetGroupMemberListEx(lbl_1_bss_2B8, 2);
    for (i = 0; i < 2; i++) {
        obj = omAddObjEx(lbl_1_bss_2B8, 100, 1, 3, 2, fn_1_1F98);
        lbl_1_bss_A4[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M533_WORK3), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    lbl_1_bss_C = -1;
    lbl_1_bss_8 = -1;
    lbl_1_bss_4 = -1;
    lbl_1_bss_0 = -1;
    omMakeGroupEx(lbl_1_bss_2B8, 4, 4);
    lbl_1_bss_A0 = omGetGroupMemberListEx(lbl_1_bss_2B8, 4);
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(lbl_1_bss_2B8, 104, 1, 2, 4, fn_1_4A44);
        lbl_1_bss_A0[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M533_WORK4), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    omMakeGroupEx(lbl_1_bss_2B8, 5, 24);
    lbl_1_bss_9C = omGetGroupMemberListEx(lbl_1_bss_2B8, 5);
    for (i = 0; i < 24; i++) {
        obj = omAddObjEx(lbl_1_bss_2B8, 105, 1, 1, 5, fn_1_4F84);
        lbl_1_bss_9C[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M533_WORK5), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    fn_1_6528();
    fn_1_6590(obj);
    lbl_1_bss_B0 = obj;
    MgSeqCreate(&lbl_1_data_4C8);
}

/* asm 464-721, 246 insns. Player object init. */
void fn_1_6A8(OMOBJ *obj)
{
    M533_PLAYER *player;
    s32 i;

    player = obj->data;
    player->playerNo = obj->work[0];
    player->charNo = GwPlayerConf[player->playerNo].charNo;
    player->grp = obj->work[1];
    player->flags = 0;
    player->stopTime = 0;
    if ((obj->work[2] & 1) == 0) {
        player->flags |= 1;
        player->rot.y = -90.0f;
    } else {
        player->flags |= 2;
        player->rot.y = 0.0f;
    }
    player->padNo = GwPlayerConf[player->playerNo].padNo;
    player->motNo = 0;
    player->cameraNo = player->grp;
    player->btn = 0;
    player->btnTime = 0;
    player->pressNum = 0;
    player->timer = 0;
    player->angle = 180.0f;
    player->angleSpeed = 3.0f;
    player->stamina = 100.0f;
    player->unk44.x = player->unk44.y = player->unk44.z = 0.0f;
    for (i = 0; i < 4; i++) {
        if (i != player->playerNo && player->grp == GwPlayerConf[i].grp) {
            player->partnerNo = i;
            break;
        }
    }
    player->dif = GwPlayerConf[player->playerNo].dif;
    if (GwPlayerConf[player->playerNo].type != 0) {
        player->difNo = player->dif;
    } else {
        player->difNo = 4;
    }
    player->comRest = 50.0f;
    fn_1_1E3C(obj);
    player->comWait = 0;
    obj->mdlId[0] = CharModelCreate(player->charNo, 4);
    lbl_1_bss_90[player->playerNo] = obj->mdlId[0];
    Hu3DModelCameraSet(obj->mdlId[0], 1 << player->cameraNo);
    for (i = 0; i < 10; i++) {
        obj->mtnId[i] = CharMotionCreate(player->charNo, lbl_1_data_20[i]);
        CharMotionSet(player->charNo, obj->mtnId[i]);
    }
    CharMotionVoiceOnSet(player->charNo, 75, FALSE);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[0]);
    player->rot.x = player->rot.z = 0.0f;
    obj->trans.x = player->pos.x = 0.0f;
    obj->trans.y = player->pos.y = 0.0f;
    obj->trans.z = player->pos.z = 0.0f;
    player->pos.x = 0.0f;
    player->pos.y = 0.0f;
    player->pos.z = 0.0f;
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    CharMotionDataClose(player->charNo);
    obj->objFunc = fn_1_A80;
}

/* asm 724-1513, 759 insns. Player object main. */
void fn_1_A80(OMOBJ *obj)
{
    M533_PLAYER *player;
    M533_PLAYER *partner;
    M533_WORK3 *boat;
    u16 mask;
    float time;
    HuVecF ofs;

    player = obj->data;
    partner = lbl_1_bss_AC[player->partnerNo]->data;
    boat = lbl_1_bss_A4[player->grp]->data;
    if (player->flags & 4) {
        fn_1_1A5C(obj, 5);
        if (--player->timer < 0) {
            fn_1_1A5C(obj, 0);
            player->flags &= ~4;
            player->flags |= 2;
            player->flags &= ~1;
            player->timer = 0;
            player->angle = 180.0f;
            player->rot.y = 0.0f;
            partner->flags &= ~8;
            partner->flags |= 1;
            partner->flags &= ~2;
            partner->timer = 0;
            partner->angle = 180.0f;
            partner->rot.y = -90.0f;
        } else {
            player->angle -= player->angleSpeed;
            player->pos.z = 100.0 * -sin(M_PI * player->angle / 180.0);
            player->rot.y -= player->angleSpeed;
            player->pos.x += 3.1666667f;
            Hu3DModelAttrReset(lbl_1_bss_4C[player->grp], HU3D_MOTATTR_LOOP);
            boat->pauseF = 0;
            player->speed = 0.0f;
            Hu3DMotionTimeSet(lbl_1_bss_4C[player->grp], 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_4C[player->grp], 0.0f);
        }
    } else if (player->flags & 8) {
        lbl_1_bss_44[player->grp] = 99.0f;
        fn_1_1A5C(obj, 5);
        if (--player->timer < 0) {
            fn_1_1A5C(obj, 0);
            fn_1_1E3C(obj);
        } else {
            player->angle -= player->angleSpeed;
            player->pos.z = 100.0 * sin(M_PI * player->angle / 180.0);
            player->rot.y -= player->angleSpeed;
            player->pos.x -= 3.1666667f;
        }
    }
    if (MgSeqModeGet() == MGSEQ_MODE_START && (player->flags & 1)) {
        fn_1_1BA0(obj);
    }
    if (MgSeqModeGet() == MGSEQ_MODE_FINISH && MgSeqFrameNoGet() == 0) {
        fn_1_1A5C(obj, 0);
    }
    if (MgSeqModeGet() >= MGSEQ_MODE_FINISH) {
        ofs.x = boat->pos.x;
        ofs.y = boat->pos.y;
        ofs.z = boat->pos.z;
        omSetTra(obj, player->pos.x + ofs.x, player->pos.y + ofs.y, player->pos.z + ofs.z);
        omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
        return;
    }
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
        if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
            if (MgSeqFrameNoGet() == 0) {
                if (player->flags & 1) {
                    obj->trans.x = player->pos.x = lbl_1_data_4FC.x - 80.0f;
                } else {
                    obj->trans.x = player->pos.x = 110.0f + lbl_1_data_4FC.x;
                }
                obj->trans.y = player->pos.y = lbl_1_data_4FC.y;
                obj->trans.z = player->pos.z = lbl_1_data_4FC.z;
                omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
                return;
            }
            if (MgSeqFrameNoGet() == 1) {
                if (player->flags & 1) {
                    obj->trans.x = player->pos.x = -80.0f;
                } else {
                    obj->trans.x = player->pos.x = 110.0f;
                }
                obj->trans.y = player->pos.y = 0.0f;
                obj->trans.z = player->pos.z = 0.0f;
                omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            }
        }
        if (player->flags & 1) {
            fn_1_1BA0(obj);
            if (Hu3DMotionShiftIDGet(obj->mdlId[0]) == 0) {
                Hu3DMotionSpeedSet(obj->mdlId[0], 2.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_4C[player->grp], 2.0f);
            }
            if ((player->flags & 0x20) == 0) {
                if (GwPlayerConf[player->playerNo].type != 0) {
                    player->btn |= fn_1_1CD0(obj);
                } else {
                    player->btn |= HuPadBtnDown[player->padNo];
                }
            }
            mask = PAD_TRIGGER_R | PAD_TRIGGER_L;
            if ((player->btn & PAD_BUTTON_Y) && (player->flags & 0x20) == 0) {
                player->flags |= 0x20;
            }
            if ((player->flags & 0x20) && player->motNo == 3) {
                if (Hu3DMotionEndCheck(obj->mdlId[0]) || Hu3DMotionTimeGet(obj->mdlId[0]) == 0.0f) {
                    player->btn = 0;
                    player->flags &= ~1;
                    player->flags |= 4;
                    player->timer = 60;
                    player->rot.y = 180.0f;
                    player->flags &= ~0x20;
                    partner->flags &= ~2;
                    partner->flags |= 8;
                    partner->timer = 60;
                    partner->rot.y = 0.0f;
                }
            }
            if (mask == (player->btn & mask)) {
                player->btn &= ~mask;
                player->btnTime = 0;
                player->pressInterval = MgSeqFrameNoGet() - player->pressFrame;
                player->pressFrame = MgSeqFrameNoGet();
                player->speed = 0.25f * (2.0f * fn_1_45B8(player->pressInterval));
                Hu3DMotionSpeedSet(obj->mdlId[0], player->speed);
                Hu3DMotionSpeedSet(lbl_1_bss_4C[player->grp], player->speed);
                boat->speed += 1.5f;
                player->pressNum++;
                if (boat->pos.x < 10670.0f) {
                    player->stamina -= lbl_1_data_5A0[player->difNo];
                    if (player->stamina < 0.0f) {
                        player->stamina = 0.0f;
                    }
                }
            }
            if (player->btn != 0) {
                if (++player->btnTime >= 6) {
                    player->btn &= ~mask;
                    player->btnTime = 0;
                }
            }
            if (player->motNo == 3) {
                if (MgSeqFrameNoGet() - player->pressFrame > 30) {
                    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrReset(lbl_1_bss_4C[player->grp], HU3D_MOTATTR_LOOP);
                    boat->pauseF = 0;
                } else {
                    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrSet(lbl_1_bss_4C[player->grp], HU3D_MOTATTR_LOOP);
                    boat->pauseF = 1;
                }
            }
        }
        if (player->flags & 2) {
            player->btn = HuPadBtnDown[player->padNo];
            if (GwPlayerConf[player->playerNo].type == 0 && (player->btn & PAD_BUTTON_A) && Hu3DMotionEndCheck(lbl_1_bss_50[player->grp])) {
                HuAudFXPlay(1978);
                Hu3DMotionTimeSet(lbl_1_bss_50[player->grp], 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_50[player->grp], 1.0f);
                Hu3DMotionClusterSpeedSet(lbl_1_bss_50[player->grp], 0, 1.0f);
                Hu3DMotionClusterTimeSet(lbl_1_bss_50[player->grp], 0, 0.0f);
            }
            if (player->stamina < 100.0f) {
                fn_1_1A5C(obj, 6);
                player->stamina += lbl_1_data_5B4[player->difNo] / 60.0f;
                if (player->stamina > 100.0f) {
                    player->stamina = 100.0f;
                }
            } else {
                fn_1_1A5C(obj, 0);
            }
        }
        ofs.x = boat->pos.x;
        ofs.y = boat->pos.y;
        ofs.z = boat->pos.z;
        omSetTra(obj, player->pos.x + ofs.x, player->pos.y + ofs.y, player->pos.z + ofs.z);
        omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
        if (boat->speed > 0.0f && (player->flags & 1)) {
            time = Hu3DMotionTimeGet(lbl_1_bss_4C[player->grp]);
            if (time < lbl_1_bss_44[player->grp]) {
                if (boat->team == 0) {
                    HuAudFXPlay(1976);
                } else if (boat->team == 1) {
                    HuAudFXPlay(1976);
                }
            }
            lbl_1_bss_44[player->grp] = time;
        }
    }
}

/* asm 1516-1638, 121 insns. Group 1 object init. */
void fn_1_165C(OMOBJ *obj)
{
    M533_WORK2 *work;
    M533_PLAYER *player;

    work = obj->data;
    work->no = obj->work[0];
    player = lbl_1_bss_AC[work->no]->data;
    obj->mdlId[0] = Hu3DModelCreateData(0x5B0009);
    lbl_1_bss_88[work->no] = obj->mdlId[0];
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(obj->mdlId[0], 1 << player->cameraNo);
    obj->trans.x = work->pos.x = 0.0f;
    obj->trans.y = work->pos.y = 0.0f;
    obj->trans.z = work->pos.z = 0.0f;
    work->pos.x = 0.0f;
    work->pos.y = 0.0f;
    work->pos.z = 0.0f;
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, lbl_1_data_50[player->charNo], lbl_1_data_50[player->charNo], lbl_1_data_50[player->charNo]);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    obj->objFunc = fn_1_1840;
}

/* asm 1641-1784, 135 insns. Group 1 object main. */
void fn_1_1840(OMOBJ *obj)
{
    M533_WORK2 *work;
    M533_PLAYER *player;
    M533_WORK3 *boat;
    HuVecF ofs;

    work = obj->data;
    player = lbl_1_bss_AC[work->no]->data;
    boat = lbl_1_bss_A4[player->grp]->data;
    if (MgSeqModeGet() >= MGSEQ_MODE_MAIN) {
        if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
            if (MgSeqFrameNoGet() == 0) {
                if (player->flags & 1) {
                    obj->trans.x = work->pos.x = lbl_1_data_4FC.x - 80.0f;
                } else {
                    obj->trans.x = work->pos.x = 110.0f + lbl_1_data_4FC.x;
                }
                obj->trans.y = work->pos.y = lbl_1_data_4FC.y;
                obj->trans.z = work->pos.z = lbl_1_data_4FC.z;
                omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
                return;
            }
            if (MgSeqFrameNoGet() == 1) {
                if (player->flags & 1) {
                    obj->trans.x = work->pos.x = -80.0f;
                } else {
                    obj->trans.x = work->pos.x = 110.0f;
                }
                obj->trans.y = work->pos.y = 0.0f;
                obj->trans.z = work->pos.z = 0.0f;
                omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
            }
        }
        ofs.x = boat->pos.x;
        ofs.y = boat->pos.y;
        ofs.z = boat->pos.z;
        work->pos.x = player->pos.x;
        work->pos.y = player->pos.y;
        work->pos.z = player->pos.z;
        omSetTra(obj, work->pos.x + ofs.x, work->pos.y + ofs.y, work->pos.z + ofs.z);
    }
}

/* asm 1787-1824, 35 insns. */
void fn_1_1A5C(OMOBJ *obj, s32 motNo)
{
    M533_PLAYER *player = obj->data;

    if (player->motNo != motNo) {
        player->motNo = motNo;
        CharMotionShiftSet(player->charNo, obj->mtnId[player->motNo], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    }
}

/* asm 1827-1875, 46 insns. Unreferenced. */
void fn_1_1AE8(OMOBJ *obj, s32 motNo, float shift, u32 attr)
{
    M533_PLAYER *player = obj->data;

    if (player->motNo != motNo) {
        player->motNo = motNo;
        CharMotionShiftSet(player->charNo, obj->mtnId[player->motNo], 0.0f, shift, attr);
        if (lbl_1_bss_30 == -1 && motNo == 2) {
            CharFXPlay(player->charNo, 512);
        }
    }
}

/* asm 1878-1957, 76 insns. */
void fn_1_1BA0(OMOBJ *obj)
{
    M533_PLAYER *player = obj->data;

    if (player->motNo != 3) {
        player->motNo = 3;
        Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[player->motNo], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
        player->stopTime = 8;
    } else if (player->stopTime-- == 0) {
        Hu3DMotionTimeSet(obj->mdlId[0], 0.0f);
        Hu3DMotionSpeedSet(obj->mdlId[0], 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_4C[player->grp], 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_4C[player->grp], 0.0f);
        player->speed = 0.0f;
    }
}

/* asm 1960-2020, 55 insns. */
u16 fn_1_1CD0(OMOBJ *obj)
{
    M533_PLAYER *player;
    M533_WORK3 *boat;
    u16 btn;

    player = obj->data;
    boat = lbl_1_bss_A4[player->grp]->data;
    btn = 0;
    player->comWaitMax = player->comWaitNext;
    if (player->stamina > player->comRest || boat->pos.x >= 10670.0f) {
        if (player->comWait >= player->comWaitMax) {
            btn = PAD_TRIGGER_R | PAD_TRIGGER_L;
            player->comWait = 0;
            fn_1_1E3C(obj);
        } else {
            player->comWait++;
            btn = 0;
        }
    } else {
        btn = PAD_BUTTON_Y;
    }
    return btn;
}

/* asm 2023-2060, 36 insns. Unreferenced. */
void fn_1_1DAC(OMOBJ *obj)
{
    M533_PLAYER *player;
    float max;
    float min;

    player = obj->data;
    max = player->comRestMax;
    min = player->comRestMin;
    player->comRest = min + frandmod(max - min);
}

/* asm 2063-2154, 87 insns. */
void fn_1_1E3C(OMOBJ *obj)
{
    M533_PLAYER *player;
    s32 max;
    s32 min;

    player = obj->data;
    if (player->stamina <= 100.0f && player->stamina >= 80.0f) {
        max = lbl_1_data_540[player->difNo][1];
        min = lbl_1_data_540[player->difNo][0];
    } else if (player->stamina <= 79.0f && player->stamina >= 60.0f) {
        max = lbl_1_data_540[player->difNo][3];
        min = lbl_1_data_540[player->difNo][2];
    } else {
        max = lbl_1_data_540[player->difNo][5];
        min = lbl_1_data_540[player->difNo][4];
    }
    player->comWaitNext = min + frandmod(max - min);
}

/* asm 2157-2614, 448 insns. Group 2 object init. */
void fn_1_1F98(OMOBJ *obj)
{
    M533_WORK3 *work;
    M533_PLAYER *player[4];
    s32 i;
    s32 mdlNo;
    s32 playerNo;
    s16 frontNo;
    s16 backNo;

    work = obj->data;
    for (i = 0; i < 4; i++) {
        player[i] = lbl_1_bss_AC[i]->data;
    }
    work->team = obj->work[0];
    work->bobAngle = 0.0f;
    work->work4F = 0;
    work->work5F = 0;
    work->speed = work->unk28 = work->unk2C = 0.0f;
    work->dist = 0.0f;
    work->goalF = 0;
    mdlNo = 0;
    if (work->team == 0) {
        playerNo = fn_1_2698(0);
        if (player[playerNo]->flags & 1) {
            frontNo = playerNo;
            backNo = player[playerNo]->partnerNo;
        } else {
            backNo = playerNo;
            frontNo = player[playerNo]->partnerNo;
        }
        obj->mdlId[mdlNo] = Hu3DModelCreateData(lbl_1_data_84[0]);
    } else {
        playerNo = fn_1_2698(1);
        if (player[playerNo]->flags & 1) {
            frontNo = playerNo;
            backNo = player[playerNo]->partnerNo;
        } else {
            backNo = playerNo;
            frontNo = player[playerNo]->partnerNo;
        }
        obj->mdlId[mdlNo] = Hu3DModelCreateData(lbl_1_data_84[1]);
    }
    lbl_1_bss_84[work->team] = obj->mdlId[mdlNo];
    Hu3DModelCameraSet(obj->mdlId[mdlNo], 1 << work->team);
    Hu3DMotionSpeedSet(obj->mdlId[mdlNo], 0.0f);
    Hu3DModelAttrSet(obj->mdlId[mdlNo], HU3D_ATTR_DISPOFF);
    work->rot.x = work->rot.y = work->rot.z = 0.0f;
    work->pos.x = 0.0f;
    work->pos.y = 0.0f;
    work->pos.z = 0.0f;
    obj->trans.x = work->pos.x = lbl_1_data_4F0.x;
    obj->trans.y = work->pos.y = lbl_1_data_4F0.y;
    obj->trans.z = work->pos.z = lbl_1_data_4F0.z;
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    lbl_1_bss_50[work->team] = Hu3DModelCreateData(lbl_1_data_84[3]);
    Hu3DModelAttrSet(lbl_1_bss_50[work->team], HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_50[work->team], 1 << work->team);
    Hu3DModelPosSet(lbl_1_bss_50[work->team], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_50[work->team], 0.0f, 0.0f, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_50[work->team], 0.0f);
    Hu3DMotionTimeSet(lbl_1_bss_50[work->team], Hu3DMotionMaxTimeGet(lbl_1_bss_50[work->team]));
    lbl_1_bss_4C[work->team] = Hu3DModelCreateData(lbl_1_data_84[2]);
    Hu3DModelAttrSet(lbl_1_bss_4C[work->team], HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_4C[work->team], 1 << work->team);
    Hu3DModelPosSet(lbl_1_bss_4C[work->team], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_4C[work->team], 0.0f, 0.0f, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_4C[work->team], 0.0f);
    lbl_1_bss_44[work->team] = 99.0f;
    Hu3DModelHookSet(lbl_1_bss_84[work->team], "itemhook_play", lbl_1_bss_90[frontNo]);
    Hu3DModelHookSet(lbl_1_bss_84[work->team], "itemhook_taiki", lbl_1_bss_90[backNo]);
    Hu3DModelHookSet(lbl_1_bss_84[work->team], "front_itemhook", lbl_1_bss_50[work->team]);
    Hu3DModelHookSet(lbl_1_bss_84[work->team], "back_itemhook", lbl_1_bss_4C[work->team]);
    Hu3DModelAttrReset(obj->mdlId[mdlNo], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_50[work->team], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_4C[work->team], HU3D_ATTR_DISPOFF);
    obj->objFunc = fn_1_2724;
}

/* asm 2617-2659, 35 insns. */
s32 fn_1_2698(s32 grp)
{
    M533_PLAYER *player[4];
    s32 i;
    s32 playerNo;

    for (i = 0; i < 4; i++) {
        player[i] = lbl_1_bss_AC[i]->data;
    }
    for (i = 0; i < 4; i++) {
        if (grp == player[i]->grp) {
            playerNo = i;
            break;
        }
    }
    return playerNo;
}

/* asm 2662-3084, 394 insns. Group 2 object main. */
void fn_1_2724(OMOBJ *obj)
{
    M533_WORK3 *work;
    M533_WORK4 *work4[4];
    M533_WORK5 *work5[24];
    s32 i;

    work = obj->data;
    for (i = 0; i < 4; i++) {
        work4[i] = lbl_1_bss_A0[i]->data;
    }
    for (i = 0; i < 24; i++) {
        work5[i] = lbl_1_bss_9C[i]->data;
    }
    if (5.0f < work->speed) {
        work->speed = 5.0f;
    }
    work->pos.x += work->speed;
    work->dist += work->speed;
    if (MgSeqModeGet() >= MGSEQ_MODE_MAIN) {
        work->bobAngle += 2.0f;
        if (work->bobAngle > 360.0f) {
            work->bobAngle = 0.0f;
        }
        work->pos.y = lbl_1_data_4FC.y + 20.0 * sin(M_PI * work->bobAngle / 180.0);
    }
    if (work->work4F == 0 && work->dist > 3333.0f) {
        if (work->team == 0) {
            if (work4[0]->activeF == 0) {
                work4[0]->activeF = 1;
                work4[2]->activeF = 1;
            }
        } else {
            if (work4[1]->activeF == 0) {
                work4[1]->activeF = 1;
                work4[3]->activeF = 1;
            }
        }
        work->work4F = 1;
    }
    if (work->work5F == 0 && work->pos.x > 6000.0f) {
        if (work->team == 0) {
            if (work5[0]->activeF == 0) {
                for (i = 0; i < 24; i += 2) {
                    work5[i]->activeF = 1;
                    if (i > 12) {
                        Hu3DModelAttrSet(lbl_1_bss_54[i], HU3D_ATTR_DISPOFF);
                    }
                }
            }
        } else {
            if (work5[1]->activeF == 0) {
                for (i = 1; i < 24; i += 2) {
                    work5[i]->activeF = 1;
                    if (i > 12) {
                        Hu3DModelAttrSet(lbl_1_bss_54[i], HU3D_ATTR_DISPOFF);
                    }
                }
            }
        }
        work->work5F = 1;
    }
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
        work->speed -= 0.05f;
        if (work->speed < 0.0f) {
            work->speed = 0.0f;
        }
    }
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN && MgSeqFrameNoGet() == 0) {
        obj->trans.x = work->pos.x = lbl_1_data_4FC.x;
        obj->trans.y = work->pos.y = lbl_1_data_4FC.y;
        obj->trans.z = work->pos.z = lbl_1_data_4FC.z;
        Hu3DMotionTimeSet(obj->mdlId[0], 0.0f);
        Hu3DMotionSpeedSet(obj->mdlId[0], 0.0f);
        Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_LOOP);
        Hu3DModelHookObjReset(obj->mdlId[0], "itemhook_play");
        Hu3DModelHookObjReset(obj->mdlId[0], "itemhook_taiki");
        Hu3DModelHookObjReset(obj->mdlId[0], "itemhook_p_shadow");
        Hu3DModelHookObjReset(obj->mdlId[0], "itemhook_t_shadow");
    }
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    if (MgSeqModeGet() >= MGSEQ_MODE_MAIN) {
        CenterM[work->team].x = work->pos.x;
        CenterM[work->team].y = 0.0f;
        CenterM[work->team].z = work->pos.z;
    }
    if (work->pos.x >= 11170.0f) {
        work->dist = 9670.0f;
        work->goalF = 1;
        if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
            MgSeqModeNext();
            lbl_1_bss_2C = MgSeqFrameNoGet();
        }
    }
    if (work->team == 0) {
        if (work->speed > 0.0f) {
            if (lbl_1_bss_C == -1) {
                lbl_1_bss_C = HuAudFXPlay(1975);
            }
        } else if (lbl_1_bss_C != -1) {
            HuAudFXStop(lbl_1_bss_C);
            lbl_1_bss_C = -1;
        }
    } else {
        if (work->speed > 0.0f) {
            if (lbl_1_bss_8 == -1) {
                lbl_1_bss_8 = HuAudFXPlay(1975);
            }
        } else if (lbl_1_bss_8 != -1) {
            HuAudFXStop(lbl_1_bss_8);
            lbl_1_bss_8 = -1;
        }
    }
}

/* asm 3087-3541, 438 insns. MGSEQ init hook. */
void fn_1_2D4C(s16 mode, s16 frameNo)
{
    M533_WORK3 *boat[2];
    M533_PLAYER *player[4];
    s32 i;
    s32 playerNo;
    s16 frontNo;
    s16 backNo;

    for (i = 0; i < 2; i++) {
        boat[i] = lbl_1_bss_A4[i]->data;
    }
    for (i = 0; i < 4; i++) {
        player[i] = lbl_1_bss_AC[i]->data;
    }
    lbl_1_bss_28 = 0;
    fn_1_44D4();
    lbl_1_bss_24 = 0.0f;
    lbl_1_bss_10[5] = Hu3DModelCreateData(lbl_1_data_84[5]);
    Hu3DModelAttrSet(lbl_1_bss_10[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_10[5], HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(lbl_1_bss_10[5], 3);
    Hu3DModelPosSet(lbl_1_bss_10[5], 0.0f, 300.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_10[5], 0.0f, 0.0f, 0.0f);
    lbl_1_bss_10[4] = Hu3DModelCreateData(lbl_1_data_84[4]);
    Hu3DModelAttrSet(lbl_1_bss_10[4], HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_10[4], 3);
    Hu3DModelPosSet(lbl_1_bss_10[4], 0.0f, 300.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_10[4], 0.0f, 0.0f, 0.0f);
    lbl_1_bss_10[6] = Hu3DModelCreateData(lbl_1_data_84[6]);
    Hu3DModelAttrSet(lbl_1_bss_10[6], HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_10[6], 3);
    Hu3DModelPosSet(lbl_1_bss_10[6], 0.0f, 300.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_10[6], 0.0f, 0.0f, 0.0f);
    lbl_1_bss_10[7] = Hu3DModelCreateData(lbl_1_data_84[7]);
    Hu3DModelAttrSet(lbl_1_bss_10[7], HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_10[7], 3);
    Hu3DModelPosSet(lbl_1_bss_10[7], 0.0f, 300.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_10[7], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_10[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_10[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_10[6], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_10[7], HU3D_ATTR_DISPOFF);
    lbl_1_bss_40 = espEntry(0x5B000D, 10, 0);
    espDispOff(lbl_1_bss_40);
    espDrawNoSet(lbl_1_bss_40, 0);
    espPosSet(lbl_1_bss_40, 16.0f, 224.0f);
    lbl_1_bss_3E = espEntry(0x5B000E, 10, 0);
    espDispOff(lbl_1_bss_3E);
    espDrawNoSet(lbl_1_bss_3E, 0);
    espPosSet(lbl_1_bss_3E, 16.0f, 256.0f);
    lbl_1_bss_3C = espEntry(0x5B000C, 11, 0);
    espDispOff(lbl_1_bss_3C);
    espDrawNoSet(lbl_1_bss_3C, 0);
    espPosSet(lbl_1_bss_3C, 320.0f, 240.0f);
    fn_1_48BC(0);
    for (i = 0; i < 2; i++) {
        playerNo = fn_1_2698(i);
        if (player[playerNo]->flags & 1) {
            frontNo = playerNo;
            backNo = player[playerNo]->partnerNo;
        } else {
            backNo = playerNo;
            frontNo = player[playerNo]->partnerNo;
        }
        Hu3DModelHookSet(lbl_1_bss_84[boat[i]->team], "itemhook_p_shadow", lbl_1_bss_88[frontNo]);
        Hu3DModelHookSet(lbl_1_bss_84[boat[i]->team], "itemhook_t_shadow", lbl_1_bss_88[backNo]);
    }
    if (WipeCheckEnd() == 0) {
        MgSeqModeNext();
    }
}

/* asm 3544-3854, 283 insns. MGSEQ fade-in hook. */
void fn_1_3424(s16 mode, s16 frameNo)
{
    s16 moveF;
    M533_WORK3 *boat[2];
    M533_PLAYER *player[4];
    s32 i;
    float step;
    float s;
    float t;

    for (i = 0; i < 2; i++) {
        boat[i] = lbl_1_bss_A4[i]->data;
    }
    for (i = 0; i < 4; i++) {
        player[i] = lbl_1_bss_AC[i]->data;
    }
    fn_1_46A4(0.0f);
    lbl_1_data_1C = HuAudFXPlay(1977);
    Hu3DModelAttrReset(lbl_1_bss_10[4], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(lbl_1_bss_10[6], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(lbl_1_bss_10[7], HU3D_MOTATTR_LOOP);
    for (i = 0; i < 125; i++) {
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        omVibrate(i, 15, 12, 0);
    }
    HuAudFXPlay(1974);
    for (i = 0; i < 2; i++) {
        Hu3DMotionTimeSet(lbl_1_bss_84[i], 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_84[i], 1.0f);
    }
    for (i = 0; i < 10; i++) {
        HuPrcVSleep();
    }
    moveF = omCameraViewMoveSimpleMulti(3, &lbl_1_data_524, 240);
    for (i = 0; i < 4; i++) {
        fn_1_1A5C(lbl_1_bss_AC[i], 7);
        if (player[i]->grp == 0) {
            CharFXPlay(player[i]->charNo, 511);
        }
    }
    for (i = 0; i < 120; i++) {
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        fn_1_1AE8(lbl_1_bss_AC[i], 0, 10.0f, HU3D_MOTATTR_LOOP);
    }
    for (i = 0; i < 17; i++) {
        HuPrcVSleep();
    }
    for (i = 0; i < 55.0f; i++) {
        HuPrcVSleep();
    }
    step = 1.0f / 60.0f;
    t = 0.0f;
    do {
        s = sin(M_PI * (90.0f * t) / 180.0);
        s *= s;
        fn_1_46A4(0.5f * s);
        HuPrcVSleep();
        t += step;
    } while (t < 1.0f);
    fn_1_48BC(1);
    mathMusicNo = HuAudSStreamPlay(51);
    MgSeqModeNext();
}

/* asm 3857-3911, 48 insns. MGSEQ main hook. */
void fn_1_3890(s16 mode, s16 frameNo)
{
    M533_WORK3 *boat[2];
    M533_PLAYER *player[4];
    s32 i;
    u32 time;

    fn_1_44D4();
    for (i = 0; i < 4; i++) {
        player[i] = lbl_1_bss_AC[i]->data;
    }
    for (i = 0; i < 2; i++) {
        boat[i] = lbl_1_bss_AC[i]->data;
    }
    fn_1_48B8();
    time = MgSeqTimerValueGet();
    if (time == 0) {
        MgSeqModeNext();
    }
    fn_1_48BC(1);
}

/* asm 3914-4188, 256 insns. MGSEQ finish hook. */
void fn_1_3950(s16 mode, s16 frameNo)
{
    M533_WORK3 *boat[2];
    s32 winner[2];
    M533_PLAYER *player[4];
    s32 i;
    s32 num;

    fn_1_44D4();
    if (MgSeqFrameNoGet() == 0) {
        HuAudSStreamFadeOut(mathMusicNo, 100);
        for (i = 0; i < 4; i++) {
            lbl_1_bss_34[i] = -1;
            player[i] = lbl_1_bss_AC[i]->data;
            if (player[i]->flags & 1) {
                fn_1_1AE8(lbl_1_bss_AC[i], 0, 8.0f, HU3D_MOTATTR_LOOP);
            }
        }
        for (i = 0; i < 2; i++) {
            boat[i] = lbl_1_bss_A4[i]->data;
            Hu3DModelAttrReset(lbl_1_bss_4C[i], HU3D_MOTATTR_LOOP);
            boat[i]->pauseF = 0;
        }
        if (boat[0]->goalF == 0 && boat[1]->goalF == 0) {
            lbl_1_bss_30 = -1;
        } else if (boat[0]->goalF != 0 && boat[1]->goalF != 0) {
            lbl_1_bss_30 = frandmod(2);
        } else if (boat[0]->goalF != 0) {
            lbl_1_bss_30 = 0;
        } else {
            lbl_1_bss_30 = 1;
        }
        if (lbl_1_bss_30 == 0) {
            fn_1_6770(lbl_1_bss_B0, 1);
        } else if (lbl_1_bss_30 == 1) {
            fn_1_6770(lbl_1_bss_B0, 2);
        }
        for (i = 0, num = 0; i < 4; i++) {
            if (lbl_1_bss_30 == player[i]->grp) {
                lbl_1_bss_34[num] = player[i]->charNo;
                winner[num] = player[i]->playerNo;
                num++;
                GWMgCoinBonusSet(i, GWMgCoinBonusGet(i) + 10);
            }
        }
        if (lbl_1_bss_30 == -1) {
            MgSeqWinnerSet(CHARNO_NONE, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
        } else if (player[winner[0]]->flags & 1) {
            MgSeqWinnerSet(lbl_1_bss_34[0], lbl_1_bss_34[1], CHARNO_NONE, CHARNO_NONE);
        } else {
            MgSeqWinnerSet(lbl_1_bss_34[1], lbl_1_bss_34[0], CHARNO_NONE, CHARNO_NONE);
        }
    }
}

/* asm 4191-4407, 204 insns. MGSEQ pre-winner hook; reads frameNo. */
void fn_1_3D50(s16 mode, s16 frameNo)
{
    M533_WORK3 *boat[2];
    M533_PLAYER *player[4];
    OMCAMERAVIEW view;
    s32 i;
    float step;
    float t;
    float s;

    fn_1_44D4();
    for (i = 0; i < 4; i++) {
        player[i] = lbl_1_bss_AC[i]->data;
    }
    for (i = 0; i < 2; i++) {
        boat[i] = lbl_1_bss_A4[i]->data;
    }
    if (lbl_1_bss_30 == -1) {
        if (frameNo == 60) {
            MgSeqModeNext();
        }
    } else if (MgSeqFrameNoGet() >= 60) {
        view.center.x = 50.0f + boat[lbl_1_bss_30]->pos.x;
        view.center.y = 100.0f + boat[lbl_1_bss_30]->pos.y;
        view.center.z = boat[lbl_1_bss_30]->pos.z;
        view.rot.x = 0.0f;
        view.rot.y = 0.0f;
        view.rot.z = 0.0f;
        view.zoom = 1200.0f;
        if (lbl_1_bss_2C < 2400) {
            fn_1_52C4();
        }
        fn_1_48BC(0);
        step = 1.0f / 60.0f;
        t = 0.0f;
        if (lbl_1_bss_30 == 0) {
            do {
                s = sin(M_PI * (90.0f * t) / 180.0);
                s *= s;
                fn_1_46A4(0.5f - 0.5f * s);
                HuPrcVSleep();
                t += step;
            } while (t < 1.0f);
            fn_1_46A4(0.0f);
        } else {
            do {
                s = sin(M_PI * (90.0f * t) / 180.0);
                s *= s;
                fn_1_46A4(0.5f + 0.5f * s);
                HuPrcVSleep();
                t += step;
            } while (t < 1.0f);
            fn_1_46A4(1.0f);
        }
        MgSeqModeNext();
    }
}

/* asm 4410-4705, 277 insns. MGSEQ winner hook. */
void fn_1_4080(s16 mode, s16 frameNo)
{
    M533_PLAYER *player[4];
    s32 i;
    s32 j;

    fn_1_44D4();
    for (i = 0; i < 4; i++) {
        player[i] = lbl_1_bss_AC[i]->data;
    }
    if (lbl_1_bss_30 == -1) {
        for (i = 0; i < 4; i++) {
            fn_1_1AE8(lbl_1_bss_AC[i], 2, 8.0f, HU3D_MOTATTR_NONE);
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_30 == player[i]->grp) {
                if (player[i]->charNo == 6) {
                    fn_1_1AE8(lbl_1_bss_AC[i], 8, 8.0f, HU3D_MOTATTR_NONE);
                } else if (player[i]->charNo == 8) {
                    fn_1_1AE8(lbl_1_bss_AC[i], 9, 8.0f, HU3D_MOTATTR_NONE);
                } else {
                    fn_1_1AE8(lbl_1_bss_AC[i], 1, 8.0f, HU3D_MOTATTR_NONE);
                }
            } else {
                fn_1_1AE8(lbl_1_bss_AC[i], 2, 8.0f, HU3D_MOTATTR_NONE);
            }
        }
    }
    for (j = 0; j < 4; j++) {
        if (player[j]->flags & 1) {
            if (player[j]->rot.y < 0.0f) {
                player[j]->rot.y += 11.25f;
                player[j]->pos.x += 1.25f;
            } else {
                player[j]->rot.y = 0.0f;
            }
        }
    }
}

/* asm 4708-4710, 1 insn. Empty. */
void fn_1_44D4(void)
{
}

/* asm 4713-4772, 56 insns. Unreferenced: debug position print. */
void fn_1_44D8(void)
{
    GXColor color;
    M533_PLAYER *player[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        player[i] = lbl_1_bss_AC[i]->data;
    }
    color.a = 192;
    color.r = 0;
    color.g = 0;
    color.b = 144;
    printWin(16, 40, 480, 96, &color);
    fontcolor = 14;
    print8(16, 40, 1.5f, "POSX:%.02f POSY:%.02f POSZ:%.02f", player[0]->pos.x, player[0]->pos.y, player[0]->pos.z);
}

/* asm 4775-4842, 59 insns. */
float fn_1_45B8(s32 rank)
{
    float speed;

    if (rank >= 1 && rank <= 5) {
        speed = 4.0f;
    } else if (rank >= 6 && rank <= 10) {
        speed = 3.5f;
    } else if (rank >= 11 && rank <= 15) {
        speed = 3.0f;
    } else if (rank >= 16 && rank <= 20) {
        speed = 2.5f;
    } else if (rank >= 21 && rank <= 25) {
        speed = 2.0f;
    } else if (rank >= 26 && rank <= 30) {
        speed = 1.5f;
    } else {
        speed = 1.0f;
    }
    return speed;
}

/* asm 4845-4979, 133 insns. Split-screen viewports and scissors. */
void fn_1_46A4(float x)
{
    Hu3DCameraPerspectiveSet(1, 30.0f, 10.0f, 10000.0f, 1.3333334f);
    Hu3DCameraViewportSet(1, 0.0f, -(480.0f * x / 2.0f), 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480.0f * (1.0f - x));
    Hu3DCameraPerspectiveSet(2, 30.0f, 10.0f, 10000.0f, 1.3333334f);
    Hu3DCameraViewportSet(2, 0.0f, (480.0f - 480.0f * x) / 2.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 0, 480.0f - 480.0f * x, 640, 480.0f * x);
}

/* asm 4982-4984, 1 insn. Empty. */
void fn_1_48B8(void)
{
}

/* asm 4987-5090, 98 insns. */
void fn_1_48BC(s32 show)
{
    M533_WORK3 *boat[2];
    s32 i;
    float x;

    for (i = 0; i < 2; i++) {
        boat[i] = lbl_1_bss_A4[i]->data;
    }
    x = 512.0f * (boat[0]->dist / 10000.0f);
    espPosSet(lbl_1_bss_40, 32.0f + x, 224.0f);
    x = 512.0f * (boat[1]->dist / 10000.0f);
    espPosSet(lbl_1_bss_3E, 32.0f + x, 256.0f);
    if (show) {
        espDispOn(lbl_1_bss_40);
        espDispOn(lbl_1_bss_3E);
        espDispOn(lbl_1_bss_3C);
    } else {
        espDispOff(lbl_1_bss_40);
        espDispOff(lbl_1_bss_3E);
        espDispOff(lbl_1_bss_3C);
    }
}

/* asm 5093-5257, 161 insns. Group 4 object init. */
void fn_1_4A44(OMOBJ *obj)
{
    M533_WORK4 *work;
    s32 i;

    work = obj->data;
    obj->mdlId[0] = Hu3DModelCreateData(0x5B0010);
    for (i = 0; i < 2; i++) {
        obj->mtnId[i] = Hu3DJointMotionData(obj->mdlId[0], lbl_1_data_48[i]);
    }
    work->no = obj->work[0];
    work->posY = -250.0f + (1.0f / 255.0f) * (100.0f * (frand() & 0xFF));
    work->angle = 180.0 * (atan2(500.0f + obj->trans.x, 100.0f + obj->trans.y) / M_PI);
    work->activeF = 0;
    work->timerMax = work->timer = frand() % 30 + 30;
    work->amp = 0.0f;
    Hu3DModelCameraSet(obj->mdlId[0], 1 << (work->no % 2));
    obj->trans.x = lbl_1_data_A8[work->no].x;
    obj->trans.y = 300.0f + lbl_1_data_A8[work->no].y;
    obj->trans.z = lbl_1_data_A8[work->no].z;
    omSetTra(obj, obj->trans.x, obj->trans.y, obj->trans.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    obj->objFunc = fn_1_4CC8;
}

/* asm 5260-5441, 175 insns. Group 4 object main. */
void fn_1_4CC8(OMOBJ *obj)
{
    M533_WORK4 *work = obj->data;

    if (work->activeF) {
        if (0.0f == work->amp) {
            if (work->timer == 0) {
                work->amp = 8.0f + (1.0f / 255.0f) * (10.0f * (frand() & 0xFF));
            } else {
                if (work->timer == 6) {
                    Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[1], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
                    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_LOOP);
                }
                work->timer--;
                work->posY -= 1.5f;
            }
        } else {
            work->posY += work->amp * sin(M_PI * work->angle / 180.0);
            obj->trans.x += 5.0f;
            work->amp *= 0.94f;
            if (work->amp < 0.1f) {
                work->amp = 0.0f;
                work->timerMax = work->timer = frand() % 30 + 30;
                Hu3DMotionSet(obj->mdlId[0], obj->mtnId[0]);
                Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
            }
        }
        omSetTra(obj, obj->trans.x, work->posY, obj->trans.z);
        if (obj->trans.y > 1000.0f) {
            Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            omSetTra(obj, lbl_1_data_D8[work->no].x, lbl_1_data_D8[work->no].y, lbl_1_data_D8[work->no].z);
            work->activeF = 0;
        }
    }
}

/* asm 5444-5566, 116 insns. Group 5 object init. */
void fn_1_4F84(OMOBJ *obj)
{
    M533_WORK5 *work;
    M533_SPAWN *spawn;

    work = obj->data;
    work->no = obj->work[0];
    work->activeF = 0;
    work->cameraNo = work->no % 2;
    work->dist = 0.0f;
    spawn = &lbl_1_data_108[work->no];
    work->speed = spawn->speed;
    switch (spawn->type) {
        case 0:
            obj->mdlId[0] = Hu3DModelCreateData(0x5B0006);
            break;
        case 1:
            obj->mdlId[0] = Hu3DModelCreateData(0x5B0007);
            break;
        case 2:
            obj->mdlId[0] = Hu3DModelCreateData(0x5B0008);
            break;
    }
    lbl_1_bss_54[work->no] = obj->mdlId[0];
    Hu3DModelCameraSet(obj->mdlId[0], 1 << (work->no % 2));
    obj->trans.x = spawn->pos.x;
    obj->trans.y = spawn->pos.y;
    obj->trans.z = spawn->pos.z;
    omSetTra(obj, obj->trans.x, obj->trans.y, obj->trans.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    obj->objFunc = fn_1_5154;
}

/* asm 5569-5668, 92 insns. Group 5 object main. */
void fn_1_5154(OMOBJ *obj)
{
    M533_WORK5 *work;
    M533_SPAWN *spawn;

    work = obj->data;
    spawn = &lbl_1_data_2E8[work->no];
    if (work->activeF) {
        if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
            if (work->no < 12) {
                Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            }
        } else {
            Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
        }
        obj->trans.x += work->speed;
        work->dist += (work->speed < 0.0f) ? -work->speed : work->speed;
        omSetTra(obj, obj->trans.x, obj->trans.y, obj->trans.z);
        if (work->dist > 3000.0f) {
            Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            omSetTra(obj, spawn->pos.x, spawn->pos.y, spawn->pos.z);
            work->activeF = 0;
            work->speed = spawn->speed;
            work->dist = 0.0f;
        }
    }
}

/* asm 5671-5842, 160 insns. */
void fn_1_52C4(void)
{
    M533_WORK4 *work4[4];
    M533_WORK5 *work5[24];
    s32 i;

    for (i = 0; i < 4; i++) {
        work4[i] = lbl_1_bss_A0[i]->data;
    }
    for (i = 0; i < 24; i++) {
        work5[i] = lbl_1_bss_9C[i]->data;
    }
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_30 == i % 2) {
            work4[i]->activeF = 1;
            work4[i]->amp = 0.0f;
            work4[i]->angle = 180.0 * (atan2(500.0f + lbl_1_bss_A0[i]->trans.x, 100.0f + lbl_1_bss_A0[i]->trans.y) / M_PI);
            work4[i]->posY = -250.0f + (1.0f / 255.0f) * (100.0f * (frand() & 0xFF));
            Hu3DModelAttrReset(lbl_1_bss_A0[i]->mdlId[0], HU3D_ATTR_DISPOFF);
        }
    }
    for (i = 0; i < 24; i++) {
        if (lbl_1_bss_30 == i % 2) {
            work5[i]->activeF = 1;
            Hu3DModelAttrReset(lbl_1_bss_9C[i]->mdlId[0], HU3D_ATTR_DISPOFF);
        }
    }
}

/* asm 5845-5861, 15 insns. Unreferenced. */
void fn_1_5544(void)
{
    Hu3DModelKill(lbl_1_bss_10[6]);
    Hu3DModelKill(lbl_1_bss_10[7]);
}
