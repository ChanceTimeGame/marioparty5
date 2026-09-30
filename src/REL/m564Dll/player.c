/*
 * m564dll player.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m564Dll/asm/REL/m564Dll/player.s.
 */

#include "REL/m564Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"


/* cross-unit globals (header retyping proposed in OUT.h.diff) */
extern int lbl_1_bss_24;
extern MGF_CAMERAVIEW lbl_1_bss_44;
extern M564_PLAYER *lbl_1_bss_100[4];
extern M564_BOMB *lbl_1_bss_1E8[15];

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xF8 */ /* void *lbl_1_rodata_F8[8] = { (void *)0x43160000, (void *)0x42480000, (void *)0x00000000, (void *)0x00000000, (void *)fn_1_4428, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000 }; */
/* 0x118 */ /* float lbl_1_rodata_118 = 0.0f; */
/* 0x11C */ /* float lbl_1_rodata_11C = 12.0f; */
/* 0x120 */ /* float lbl_1_rodata_120 = 25.0f; */
/* 0x124 */ /* float lbl_1_rodata_124 = 0.001f; */
/* 0x128 */ /* float lbl_1_rodata_128 = 19.0f; */
/* 0x12C */ /* float lbl_1_rodata_12C = 5.0f; */
/* 0x130 */ /* double lbl_1_rodata_130 = 360; */
/* 0x138 */ /* float lbl_1_rodata_138 = -20.0f; */
/* 0x140 */ /* double lbl_1_rodata_140 = 4503601774854144; */
/* 0x148 */ /* double lbl_1_rodata_148 = 0.10000000149011612; */
/* 0x150 */ /* float lbl_1_rodata_150 = 10.0f; */
/* 0x154 */ /* float lbl_1_rodata_154 = 50.0f; */
/* 0x158 */ /* float lbl_1_rodata_158 = 150.0f; */
/* 0x160 */ /* double lbl_1_rodata_160 = 12001; */
/* 0x168 */ /* double lbl_1_rodata_168 = 0.5; */
/* 0x170 */ /* double lbl_1_rodata_170 = 3; */
/* 0x178 */ /* float lbl_1_rodata_178 = 100.0f; */
/* 0x17C */ /* float lbl_1_rodata_17C = -1.0f; */
/* 0x180 */ /* float lbl_1_rodata_180 = 0.5f; */
/* 0x184 */ /* float lbl_1_rodata_184 = 9999.9f; */

/* --- .data --- */
/* 0x118 */ unsigned int lbl_1_data_118[11] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0028, 0x008C0059, 0x008C002F, 0x008C003F, 0x008C005B, 0x008C0026, 0x008C0027, 0 };
/* 0x144 */ M564_PLAYERMOT lbl_1_data_144[11] = {
    { 0, -1, 0x40000001 },
    { 1, -1, 0x40000001 },
    { 2, -1, 0x40000001 },
    { 3, -1, 0 },
    { 4, -1, 0 },
    { 5, -1, 0 },
    { 6, -1, 0x40000001 },
    { 7, -1, 0 },
    { 0, 8, 0x40000001 },
    { 1, 8, 0x40000001 },
    { 2, 9, 0x40000001 },
};
/*
 * The player mode table. MgPlayerModeFuncSet reads MGPLAYER_MODE_MAX (18)
 * entries; retail's table has 6, so modes 6..17 are read from the .data that
 * follows (lbl_1_data_1B4's floats). The host pads it with NULLs instead.
 */
/* 0x19C */ void *lbl_1_data_19C[6] = { (void *)fn_1_44A0, (void *)fn_1_4D2C, (void *)fn_1_4E84, (void *)fn_1_4FA4, (void *)fn_1_50CC, (void *)fn_1_52AC };
/* 0x1B4 */ HuVecF lbl_1_data_1B4[4] = { { -250.0f, 0.0f, -250.0f }, { 250.0f, 0.0f, -250.0f }, { -250.0f, 0.0f, 250.0f }, { 250.0f, 0.0f, 250.0f } };
/* 0x1E4 */ float lbl_1_data_1E4[4] = { 45.0f, -45.0f, 135.0f, -135.0f };
/* 0x1F4 */ char lbl_1_data_1F4[] = "root_motion";

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x110 */ OMOBJ **lbl_1_bss_110; /* player group member list */

/* --- functions (reference order) --- */
/* 168 insns */
void fn_1_3E7C(void)
{
    MGACTOR_PARAM param = { 150.0f, 50.0f, 0, 0, fn_1_4428, 0, 0, NULL };
    s32 i;
    OMOBJ *obj;
    M564_PLAYER *work;
    HU3DMODELID mdlId;

    omMakeGroupEx(objman, 0, 4);
    lbl_1_bss_110 = omGetGroupMemberListEx(objman, 0);
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(objman, i + 0x1000, 0, 0, 0, fn_1_411C);
        lbl_1_bss_110[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M564_PLAYER), HU_MEMNUM_OVL);
        work = obj->data;
        lbl_1_bss_100[i] = work;
        MgPlayerConfSet((MGFPLAYER *)work, i);
        work->unk02C = MgPlayerCreate(i, &param, 2, lbl_1_bss_44.no, -1, lbl_1_data_118);
        MgPlayerModeFuncSet(work->unk02C, (MGPLAYER_MODE_FUNC *)lbl_1_data_19C);
        MgActorColMaskSet(work->unk02C->actor, 3);
        param.param++;
        mdlId = work->unk02C->actor->mdlId;
        Hu3DModelShadowSet(mdlId);
        Hu3DModelLayerSet(mdlId, 2);
        MgPlayerPadSet(work->unk02C, 0, 0, 0, 0);
        work->mode = 0;
        work->unk034 = 0;
        work->unk038 = -1;
        work->unk070 = 0;
        work->unk03C = 0;
        fn_1_9AC0(work);
        work->pos = lbl_1_data_1B4[work->no];
        work->unk02C->actor->rotY = lbl_1_data_1E4[work->no];
        MgActorPosUpdate(work->unk02C->actor, &lbl_1_data_1B4[work->no]);
        work->unk030 = CharModelItemHookGet(work->charNo, 2, 0);
    }
    CharEffectLayerSet(3);
}

/* 58 insns */
void fn_1_411C(OMOBJ *obj)
{
    M564_PLAYER *work = obj->data;

    MgActorPosGet(work->unk02C->actor, &work->pos);
    CharModelVoicePanSet(work->charNo, fn_1_1448(&work->pos));
    if (lbl_1_bss_24 != 2) {
        work->unk06C = 0;
        if (work->mode == 1) {
            work->mode = 0;
            work->unk06C = PAD_BUTTON_A;
        }
        MgPlayerPadSet(work->unk02C, 0, 0, work->unk06C, 0);
    } else if (work->comF) {
        work->unk064 = work->unk068 = work->unk06C = 0;
        fn_1_9ADC(work);
        MgPlayerPadSet(work->unk02C, work->unk064, work->unk068, work->unk06C, 0);
    }
}

/* 119 insns */
void fn_1_4204(MGPLAYER *player, s16 motNo)
{
    u32 attr;
    u32 charAttr;
    s16 overlay;
    HU3DMODELID mdlId;

    if (player->motNo != motNo) {
        player->motNo = motNo;
        mdlId = player->actor->mdlId;
        attr = lbl_1_data_144[motNo].unk004;
        Hu3DModelAttrReset(mdlId, 0x40000201);
        overlay = lbl_1_data_144[motNo].unk002;
        if (overlay >= 0) {
            CharMotionShiftSet(player->charNo, player->omObj->mtnId[lbl_1_data_144[motNo].unk000], 0.0f, 12.0f, attr);
            Hu3DMotionOverlaySet(mdlId, player->omObj->mtnId[overlay]);
            charAttr = 0;
            if (attr & 0x40000001) {
                charAttr |= 0x40000200;
            }
            CharModelAttrSet(player->charNo, charAttr);
        } else {
            Hu3DMotionOverlayReset(mdlId);
            if (motNo == 4 || motNo == 6) {
                CharMotionSet(player->charNo, player->omObj->mtnId[lbl_1_data_144[motNo].unk000]);
            } else {
                CharMotionShiftSet(player->charNo, player->omObj->mtnId[lbl_1_data_144[motNo].unk000], 0.0f, 12.0f, attr);
            }
        }
    }
}

/* 18 insns */
void fn_1_43E0(MGPLAYER *player, s16 mode)
{
    player->work[0] = 0;
    player->work[1] = 0;
    MgPlayerModeSet(player, mode);
}

/* 30 insns */
int fn_1_4428(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b)
{
    M564_PLAYER *work = lbl_1_bss_100[a->paramB];
    s16 bombNo = b->paramB - 4;

    if (bombNo >= 0 && a->paramB == lbl_1_bss_1E8[bombNo]->unk01A) {
        return 0;
    }
    return 1;
}

/* 547 insns */
void fn_1_44A0(MGPLAYER *player)
{
    M564_PLAYER *work = lbl_1_bss_100[player->playerNo];
    float speed;

    if (fn_1_5930(work) == 0) {
        if (HuPadBtnDown[player->padNo] & PAD_BUTTON_A) {
            if (work->unk034) {
                fn_1_57C4(work);
                return;
            }
            if (fn_1_5600(work)) {
                return;
            }
        }
        speed = player->actor->vel.x * player->actor->vel.x + player->actor->vel.z * player->actor->vel.z;
        if (work->unk034) {
            if (speed > 25.0f) {
                fn_1_4204(player, 10);
            } else if (speed > 0.001f) {
                fn_1_4204(player, 9);
            } else {
                fn_1_4204(player, 8);
            }
        } else {
            if (speed > 25.0f) {
                fn_1_4204(player, 2);
            } else if (speed > 0.001f) {
                fn_1_4204(player, 1);
            } else {
                fn_1_4204(player, 0);
            }
        }
    }
}

/* 86 insns */
void fn_1_4D2C(MGPLAYER *player)
{
    M564_PLAYER *work = lbl_1_bss_100[player->playerNo];
    s16 charNo;

    if (fn_1_5930(work) == 0) {
        if (work->unk038 == -1) {
            fn_1_43E0(player, 0);
            MgPlayerAttrReset(player, MGPLAYER_ATTR_ANGLELOCK | MGPLAYER_ATTR_MOVEOFF);
            return;
        }
        charNo = player->charNo;
        switch (player->work[0]) {
            case 0:
                if (player->work[1]++ == 15) {
                    fn_1_14D0(&lbl_1_bss_1E8[work->unk038]->unk040, 0x8D4);
                    fn_1_5D5C(player, work->unk038);
                    player->work[0] = 1;
                }
                break;
            case 1:
                if (CharMotionEndCheck(charNo) && CharMotionShiftIDGet(charNo) < 0) {
                    fn_1_43E0(player, 0);
                    MgPlayerAttrReset(player, MGPLAYER_ATTR_ANGLELOCK | MGPLAYER_ATTR_MOVEOFF);
                }
                break;
        }
    }
}

/* 72 insns */
void fn_1_4E84(MGPLAYER *player)
{
    M564_PLAYER *work = lbl_1_bss_100[player->playerNo];
    s16 charNo;

    if (fn_1_5930(work) == 0) {
        charNo = player->charNo;
        switch (player->work[0]) {
            case 0:
                if (Hu3DMotionTimeGet(player->actor->mdlId) >= 19.0f) {
                    fn_1_14D0(&lbl_1_bss_1E8[work->unk038]->unk040, 0x8D5);
                    fn_1_89EC(work->unk038);
                    fn_1_5DF4(player);
                    player->work[0] = 1;
                }
                break;
            case 1:
                if (CharMotionEndCheck(charNo)) {
                    fn_1_43E0(player, 0);
                    MgPlayerAttrReset(player, MGPLAYER_ATTR_ANGLELOCK | MGPLAYER_ATTR_MOVEOFF);
                }
                break;
        }
    }
}

/* 74 insns */
void fn_1_4FA4(MGPLAYER *player)
{
    M564_PLAYER *work = lbl_1_bss_100[player->playerNo];

    work->unk03A++;
    if (work->unk03A >= 70) {
        MgActorPauseOn(player->actor);
    } else {
        work->rot.x = -fmodf(5.0f * work->unk03A, 360.0f);
        work->rot.y = player->actor->rotY;
        work->rot.z = 0.0f;
        player->actor->vel.z = -20.0f;
    }
}

/* 120 insns */
void fn_1_50CC(MGPLAYER *player)
{
    M564_PLAYER *work = lbl_1_bss_100[player->playerNo];
    s16 charNo = player->charNo;

    switch (player->work[0]) {
        case 0:
            fn_1_4204(work->unk02C, 7);
            player->work[0] = 1;
            break;
        case 1:
            if (CharMotionEndCheck(charNo) && CharMotionShiftIDGet(charNo) < 0) {
                fn_1_43E0(player, 0);
            }
            break;
    }
}

/* 213 insns */
/*
 * Mode 5: turn back to face the camera (rotY -> 0). The __fabs result goes through
 * two named doubles because retail keeps both in separate FPRs, interleaved with the
 * floats (f31 rotY, f30 rotY2, f29/f28, f27/f26); fabs() into one double scores raw=10-16.
 */
void fn_1_52AC(MGPLAYER *player)
{
    float rotY;
    float rotY2;
    double absTmp;
    double absRot;
    double absTmp2;
    double absRot2;

    rotY = player->actor->rotY;
    absTmp = __fabs(rotY);
    absRot = absTmp;
    if (absRot > 0.1f) {
        fn_1_4204(player, 1);
        player->actor->rotY = MgAngleApproach(player->actor->rotY, 0.0f, 10.0f);
        rotY2 = player->actor->rotY;
        absTmp2 = __fabs(rotY2);
        absRot2 = absTmp2;
        if (absRot2 < 0.1f) {
            fn_1_4204(player, 0);
        }
    }
}

/* 113 insns */
int fn_1_5600(M564_PLAYER *work)
{
    work->unk038 = fn_1_8340(&work->pos, work->unk02C->actor->rotY);
    if (work->unk038 == -1) {
        return 0;
    }
    fn_1_86D8(work->unk038, work->no);
    fn_1_43E0(work->unk02C, 1);
    MgPlayerAttrSet(work->unk02C, MGPLAYER_ATTR_ANGLELOCK | MGPLAYER_ATTR_MOVEOFF);
    fn_1_4204(work->unk02C, 3);
    return 1;
}

/* 91 insns */
void fn_1_57C4(M564_PLAYER *work)
{
    fn_1_43E0(work->unk02C, 2);
    MgPlayerAttrSet(work->unk02C, MGPLAYER_ATTR_ANGLELOCK | MGPLAYER_ATTR_MOVEOFF);
    fn_1_4204(work->unk02C, 4);
}

/* 267 insns */
int fn_1_5930(M564_PLAYER *work)
{
    HU3DMODELID mdlId;
    HuVecF diff;
    HuVecF objPos;

    if (fn_1_5E5C(work->no)) {
        return 1;
    }
    if (!fn_1_8558(&work->pos, 50.0f, 150.0f) && !work->unk03C) {
        return 0;
    }
    if (work->unk034) {
        fn_1_7404(lbl_1_bss_1E8[work->unk038]);
    }
    work->unk038 = -1;
    omVibrate(work->no, 60, 12, 0);
    work->rot.x = 0.0f;
    work->rot.y = work->unk02C->actor->rotY;
    work->rot.z = 0.0f;
    work->unk03A = 0;
    fn_1_43E0(work->unk02C, 3);
    fn_1_4204(work->unk02C, 6);
    work->unk02C->actor->velY = 100.0f + 100.0f * ((-1.0f + sqrtf(12001.0f)) / 2.0f);
    MgActorColMaskSet(work->unk02C->actor, 0);
    MgPlayerAttrSet(work->unk02C, MGPLAYER_ATTR_ANGLELOCK | MGPLAYER_ATTR_MOVEOFF);
    mdlId = work->unk02C->actor->mdlId;
    Hu3DModelObjPosGet(mdlId, lbl_1_data_1F4, &objPos);
    PSVECSubtract(&work->pos, &objPos, &diff);
    PSMTXTrans(Hu3DData[mdlId].mtx, 0.0f, diff.y, 0.0f);
    work->pos.y = objPos.y;
    MgActorPosSet(work->unk02C->actor, &work->pos);
    fn_1_14D0(&work->pos, 0x8D9);
    work->unk070++;
    return 1;
}

/* 38 insns */
void fn_1_5D5C(MGPLAYER *player, s16 bombNo)
{
    M564_PLAYER *work = lbl_1_bss_100[player->playerNo];

    Hu3DModelHookSet(player->actor->mdlId, work->unk030, lbl_1_bss_1E8[bombNo]->unk004);
    work->unk034 = 1;
    fn_1_87B4(bombNo, work->no);
}

/* 26 insns */
void fn_1_5DF4(MGPLAYER *player)
{
    M564_PLAYER *work = lbl_1_bss_100[player->playerNo];

    Hu3DModelHookReset(player->actor->mdlId);
    work->unk034 = 0;
    work->unk038 = -1;
}

/* 19 insns */
int fn_1_5E5C(s16 no)
{
    if (no == -1) {
        return 1;
    }
    if (lbl_1_bss_100[no]->unk02C->mode == 3) {
        return 1;
    }
    return 0;
}

/* 24 insns */
void fn_1_5EA8(s16 no, HuVecF *pos)
{
    M564_PLAYER *work = lbl_1_bss_100[no];

    Hu3DModelObjPosGet(work->unk02C->actor->mdlId, work->unk030, pos);
}

/* 53 insns */
void fn_1_5F08(s16 no)
{
    M564_PLAYER *work = lbl_1_bss_100[no];

    if (work->unk034) {
        fn_1_5DF4(work->unk02C);
        fn_1_43E0(work->unk02C, 0);
        MgPlayerAttrSet(work->unk02C, MGPLAYER_ATTR_ANGLELOCK | MGPLAYER_ATTR_MOVEOFF);
        work->unk03C = 1;
    }
}

/* 67 insns */
s16 fn_1_5FDC(HuVecF *pos)
{
    M564_PLAYER *work;
    float dist;
    float minDist = 9999.9f;
    s16 nearNo = -1;
    int i;

    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_100[i];
        if (!fn_1_5E5C(i)) {
            dist = fn_1_13A4(pos, &work->pos);
            if (dist < minDist) {
                minDist = dist;
                nearNo = i;
            }
        }
    }
    return nearNo;
}

