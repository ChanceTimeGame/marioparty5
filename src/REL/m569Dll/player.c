/*
 * m569dll player.c -- the four players (1VS3: the solo player hits the three
 * blocks overhead, the team walks the reflection line). Functions are in
 * reference order; fn_1_4B8C must stay above fn_1_4F14..fn_1_54A8 (it is
 * inlined there) and fn_1_3D68/3E68/433C/4404 above their callers.
 * Each player has two models: obj->mdlId[0] the character, obj->mdlId[1] an
 * upside-down copy (scale y -1, HU3D_ATTR_CULL_FRONT) with its own joint
 * motions in M569_PLAYER.unk036.
 */

#include "REL/m569dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/armem.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xB0 */ /* float lbl_1_rodata_B0 = 1.0f; */
/* 0xB4 */ /* float lbl_1_rodata_B4 = -1.0f; */
/* 0xB8 */ /* float lbl_1_rodata_B8 = 0.0f; */
/* 0xBC */ /* float lbl_1_rodata_BC = 10.0f; */
/* 0xC0 */ /* float lbl_1_rodata_C0 = 100.0f; */
/* 0xC4 */ /* float lbl_1_rodata_C4 = 15.0f; */
/* 0xC8 */ /* double lbl_1_rodata_C8 = 0.10000000149011612; */
/* 0xD0 */ /* float lbl_1_rodata_D0 = 30.0f; */
/* 0xD8 */ /* double lbl_1_rodata_D8 = 4503601774854144; */
/* 0xE0 */ /* double lbl_1_rodata_E0 = 180; */
/* 0xE8 */ /* double lbl_1_rodata_E8 = 3.141592653589793; */
/* 0xF0 */ /* float lbl_1_rodata_F0[2] = { 360.0f, 0.0f }; */

/* --- .data --- */
/* Motions, terminated for CharModelMotListCreate: rows of obj->mtnId and M569_PLAYER.unk036. */
/* 0x170 */ unsigned int lbl_1_data_170[9] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C000B, 0x008C0030, 0x008C0031, 0x008C002D, 0x008C002E, 0x00000000 };
/* Start x per slot (unk02C). */
/* 0x194 */ float lbl_1_data_194[4] = { -600.0f, 600.0f, 750.0f, 900.0f };
/* Walk-in target per slot. */
/* 0x1A4 */ HuVecF lbl_1_data_1A4[4] = { { -400.0f, 0.0f, 0.0f }, { 400.0f, 0.0f, 0.0f }, { 400.0f, 0.0f, 0.0f }, { 400.0f, 0.0f, 0.0f } };
/* Team end position per slot (fn_1_4F14). */
/* 0x1D4 */ HuVecF lbl_1_data_1D4[4] = { { -400.0f, 0.0f, -300.0f }, { 260.0f, 0.0f, -450.0f }, { 330.0f, 0.0f, -300.0f }, { 400.0f, 0.0f, -150.0f } };
/* Line-up position per slot (fn_1_52F8). */
/* 0x204 */ HuVecF lbl_1_data_204[4] = { { -300.0f, 0.0f, -50.0f }, { -100.0f, 0.0f, -50.0f }, { 100.0f, 0.0f, -50.0f }, { 300.0f, 0.0f, -50.0f } };
/* 0x234 */ s32 lbl_1_data_234[1] = { 0 }; /* unreferenced trailing word of dtk's lbl_1_data_204 */

/* --- functions (reference order) --- */
/* 200 insns */
void fn_1_3A48(void)
{
    OMOBJ *obj;
    M569_PLAYER *player;
    int i;
    int j;
    HU3DMODELID modelId;
    int dirNum;
    unsigned int dataNum;
    void *data;

    omMakeGroupEx(objman, 0, 4);
    lbl_1_bss_F8 = omGetGroupMemberListEx(objman, 0);
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(objman, 0x2000, 2, 8, 0, fn_1_3F50);
        lbl_1_bss_F8[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M569_PLAYER), HU_MEMNUM_OVL);
        player = obj->data;
        MgPlayerConfSet((MGFPLAYER *)player, i);
        player->unk048 = 0;
        player->mode = 0;
        player->unk06C = 1;
        modelId = CharModelMotListCreate(player->charNo, 4, lbl_1_data_170, obj->mtnId);
        obj->mdlId[0] = modelId;
        Hu3DModelShadowSet(modelId);
        CharModelAttrSet(player->charNo, HU3D_MOTATTR_LOOP);
        player->unk030 = -1;
        dirNum = charDataDirTbl[player->charNo][3];
        modelId = Hu3DModelCreate(HuDataSelHeapReadNum(dirNum, HU_MEMNUM_OVL, HEAP_MODEL));
        HuDataDirClose(dirNum);
        for (j = 0; j < 8; j++) {
            dataNum = (lbl_1_data_170[j] & 0xFFFF) | charDataDirTbl[player->charNo][4];
            data = HuAR_ARAMtoMRAMFileRead(dataNum, HU_MEMNUM_OVL, HEAP_MODEL);
            player->unk036[j] = Hu3DJointMotion(modelId, data);
        }
        Hu3DModelScaleSet(modelId, 1.0f, -1.0f, 1.0f);
        Hu3DModelAttrSet(modelId, HU3D_ATTR_CULL_FRONT);
        Hu3DMotionSet(modelId, player->unk036[0]);
        obj->mdlId[1] = modelId;
        fn_1_4B8C(obj, 0);
    }
    CharEffectLayerSet(3);
    fn_1_4D74();
    for (i = 0; i < 4; i++) {
        player = lbl_1_bss_F8[i]->data;
        player->pos.x = lbl_1_data_194[player->unk02C];
        player->pos.z = 0.0f;
        omSetTra(lbl_1_bss_F8[i], player->pos.x, player->pos.y, player->pos.z);
        if (player->unk02C == 0) {
            player->unk046 = 0;
            player->unk068 = frandmod(3);
            player->unk06A = 0;
        } else {
            player->unk046 = player->unk02C - 1;
            player->unk068 = player->unk046;
            player->unk06A = frandmod(90) + 30;
        }
    }
}

/* 64 insns: walk toward unk050, circling the other players; TRUE on arrival. */
BOOL fn_1_3D68(OMOBJ *obj)
{
    M569_PLAYER *player = obj->data;
    HuVecF pos;
    HuVecF rot;
    M569_PLAYER *other;
    BOOL result;
    int i;

    pos = player->pos;
    result = MgVecApproach(&pos, &player->unk050, &rot, 10.0f);
    for (i = 0; i < 4; i++) {
        other = lbl_1_bss_F8[i]->data;
        if (player != other) {
            if (MgVecOrbit(&player->pos, &pos, &other->pos, 100.0f)) {
                result = FALSE;
            }
        }
    }
    player->rot.y = MgAngleApproach(player->rot.y, rot.y, 15.0f);
    player->pos = pos;
    return result;
}

/* 58 insns */
void fn_1_3E68(OMOBJ *obj)
{
    M569_PLAYER *player = obj->data;

    switch (obj->work[0]) {
        case 0:
            obj->work[0] = 1;
            player->unk050 = lbl_1_data_1A4[player->unk02C];
            CharModelAttrSet(player->charNo, HU3D_MOTATTR_LOOP);
            fn_1_4B8C(obj, 2);
            break;
        case 1:
            if (MgVecApproach(&player->pos, &player->unk050, &player->rot, 10.0f)) {
                if (player->unk02C == 0) {
                    fn_1_5138(player->no);
                } else {
                    fn_1_4F14(player->no);
                }
            }
            break;
    }
}

/* 251 insns: the player object. */
void fn_1_3F50(OMOBJ *obj)
{
    M569_PLAYER *player = obj->data;

    CharModelVoicePanSet(player->charNo, fn_1_1014(&player->pos));
    switch (player->mode) {
        case 0:
            break;
        case 1:
            fn_1_3E68(obj);
            break;
        case 2:
            fn_1_454C(obj);
            break;
        case 3:
            if (fn_1_3D68(obj)) {
                fn_1_4B8C(obj, 0);
                player->mode = 0;
            }
            break;
        case 4:
            if (fn_1_3D68(obj)) {
                fn_1_4B8C(obj, 0);
                player->mode = 5;
            }
            break;
        case 5:
            player->rot.y = MgAngleApproach(player->rot.y, player->unk05C.y, 15.0f);
            if (fabs(player->rot.y - player->unk05C.y) <= 0.1f) {
                player->rot.y = player->unk05C.y;
                player->mode = 0;
            }
            break;
    }
    Hu3DModelPosSetV(obj->mdlId[1], &player->pos);
    Hu3DModelRotSetV(obj->mdlId[1], &player->rot);
    omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
}

/* 50 insns: COM or pad wants to hit the block overhead. */
BOOL fn_1_433C(M569_PLAYER *player)
{
    if (player->unk048 != 0) {
        return FALSE;
    }
    if (fn_1_848C(player->unk046) != 1) {
        return FALSE;
    }
    if (player->comF) {
        if (player->unk06A == 0) {
            if ((s16)player->unk046 == player->unk068) {
                return TRUE;
            }
        } else {
            player->unk06A--;
        }
    } else if (HuPadBtnDown[player->padNo] & PAD_BUTTON_A) {
        return TRUE;
    }
    return FALSE;
}

/* 82 insns: COM or pad wants to step to the next block. */
BOOL fn_1_4404(M569_PLAYER *player)
{
    if (player->comF) {
        if (player->unk048 > 1) {
            return FALSE;
        }
        if (player->unk068 == -1) {
            return FALSE;
        }
        if ((s16)player->unk046 < player->unk068) {
            player->unk048 = 5;
            return TRUE;
        }
        if ((s16)player->unk046 > player->unk068) {
            player->unk048 = 4;
            return TRUE;
        }
        return FALSE;
    }
    if (player->grp != 0) {
        return FALSE;
    }
    if ((HuPadDStk[player->padNo] & PAD_BUTTON_RIGHT) && (player->unk048 <= 1 || player->unk048 == 4) && player->unk046 != 2) {
        player->unk048 = 5;
        return TRUE;
    }
    if ((HuPadDStk[player->padNo] & PAD_BUTTON_LEFT) && (player->unk048 <= 1 || player->unk048 == 5) && player->unk046 != 0) {
        player->unk048 = 4;
        return TRUE;
    }
    return FALSE;
}

/* 292 insns: mode 2, the play state. */
void fn_1_454C(OMOBJ *obj)
{
    M569_PLAYER *player = obj->data;
    BOOL over;
    int motNo;

    over = fn_1_85C0();
    if (over && player->unk048 == 0) {
        player->mode = 0;
        player->unk068 = -1;
        player->unk048 = 0;
        fn_1_4B8C(obj, 0);
        player->unk04C = fn_1_86C4();
        return;
    }
    if (player->unk048 == 2) {
        if (fn_1_848C(player->unk046) == 1 && (s16)CharModelTimingHookNoGet(player->charNo) != 0) {
            omVibrate(player->no, 12, 12, 0);
            fn_1_839C(player->unk046);
            if (player->unk02C == 0) {
                player->unk068 = fn_1_84A8();
            } else {
                player->unk068 = -1;
            }
        }
        if (CharMotionEndCheck(player->charNo)) {
            fn_1_4B8C(obj, 0);
            player->unk048 = 0;
        }
        return;
    }
    if (fn_1_433C(player)) {
        fn_1_4B8C(obj, 3);
        player->unk048 = 2;
        return;
    }
    motNo = -1;
    if (player->unk048 == 4 || player->unk048 == 5) {
        if (MgVecApproach(&player->pos, &player->unk050, &player->unk05C, 10.0f)) {
            player->unk048 = 1;
            motNo = 0;
        }
    }
    if (fn_1_4404(player) && !over) {
        if (player->unk048 == 5) {
            player->unk046++;
        } else {
            player->unk046--;
        }
        player->unk050 = player->pos;
        player->unk050.x = lbl_1_data_32C[player->unk046].x;
        motNo = 2;
    }
    if (motNo != -1) {
        fn_1_4B8C(obj, motNo);
    }
    if (player->unk048 == 1) {
        player->unk05C.y = 0.0f;
        if (fabs(player->rot.y - player->unk05C.y) <= 0.1f) {
            player->rot.y = player->unk05C.y;
            player->unk048 = 0;
        }
    }
    player->rot.y = MgAngleApproach(player->rot.y, player->unk05C.y, 30.0f);
}

/* 108 insns: SE object spawned by motions 4..7; plays the landing SE at the motion's end. */
void fn_1_49DC(OMOBJ *obj)
{
    M569_PLAYER *player = lbl_1_bss_F8[obj->work[0]]->data;
    s16 time;
    s16 seNo;
    s16 pan;

    switch (player->unk030) {
        case 4:
            seNo = 0x1F8;
            time = CharMotionTotalTimeGet(player->charNo, lbl_1_data_170[player->unk030]);
            break;
        case 6:
            seNo = 0x1FB;
            time = CharMotionTotalTimeGet(player->charNo, lbl_1_data_170[player->unk030]);
            break;
        case 5:
        case 7:
            seNo = 0x200;
            time = CharMotionExtraTimeGet(player->charNo, lbl_1_data_170[player->unk030]);
            break;
    }
    pan = fn_1_1014(&player->pos);
    if (Hu3DMotionTimeGet(lbl_1_bss_F8[obj->work[0]]->mdlId[0]) >= time && Hu3DMotionShiftIDGet(lbl_1_bss_F8[obj->work[0]]->mdlId[0]) < 0) {
        CharFXPlayPan(player->charNo, seNo, pan);
        omDelObjEx(objman, obj);
    }
}

/* 122 insns */
void fn_1_4B8C(OMOBJ *obj, int motNo)
{
    M569_PLAYER *player = obj->data;
    s16 charNo = player->charNo;
    float start = 0.0f;
    float end = 10.0f;
    u32 attr = HU3D_MOTATTR_LOOP;
    OMOBJ *seObj;

    if (player->unk030 != motNo) {
        player->unk030 = motNo;
        switch (motNo) {
            case 0: case 1: break;
            case 3:
                attr = HU3D_MOTATTR_NONE;
                end = 0.0f;
                break;
            case 4:
            case 5:
            case 6:
            case 7:
                CharMotionVoiceOnSet(player->charNo, lbl_1_data_170[motNo], FALSE);
                attr = HU3D_MOTATTR_NONE;
                end = 0.0f;
                if (player->unk06C) {
                    seObj = omAddObjEx(objman, 0x2000, 0, 0, -1, fn_1_49DC);
                    seObj->work[0] = player->no;
                }
            case 2:
                end = end; /* a no-op the original has: it keeps case 2 its own switch range */
        }
        if (0.0f != end) {
            CharMotionShiftSet(charNo, obj->mtnId[motNo], start, end, attr);
            Hu3DMotionShiftSet(obj->mdlId[1], player->unk036[motNo], start, end, attr);
        } else {
            CharModelAttrReset(charNo, 0x40000003);
            CharMotionSet(charNo, obj->mtnId[motNo]);
            Hu3DModelAttrReset(obj->mdlId[1], 0x40000003);
            Hu3DMotionSet(obj->mdlId[1], player->unk036[motNo]);
        }
    }
}

/* 80 insns: sort the players into the two sides. */
void fn_1_4D74(void)
{
    M569_PLAYER *player;
    int i;
    int j;
    int slot;
    s16 grp;

    for (i = 0; i < 2; i++) {
        memset(&lbl_1_bss_D8[i], 0, sizeof(M569_ROUND));
        for (j = 0; j < 3; j++) {
            lbl_1_bss_D8[i].unk004[j] = -1;
        }
    }
    for (i = 0; i < 4; i++) {
        player = lbl_1_bss_F8[i]->data;
        grp = player->grp;
        if (grp == 0) {
            lbl_1_bss_D8[0].unk004[0] = player->no;
            player->unk02C = 0;
            player->unk046 = 0;
        } else {
            do {
                slot = frandmod(3);
            } while (lbl_1_bss_D8[1].unk004[slot] != -1);
            lbl_1_bss_D8[1].unk004[slot] = player->no;
            player->unk02C = slot + 1;
            player->unk046 = slot;
        }
    }
}

/* 12 insns */
void fn_1_4EB4(int no, int mode)
{
    M569_PLAYER *player = lbl_1_bss_F8[no]->data;
    player->mode = mode;
}

/* 12 insns */
int fn_1_4EE4(int no)
{
    M569_PLAYER *player = lbl_1_bss_F8[no]->data;
    return player->mode;
}

/* 137 insns: team player walks to its end position, facing the camera. */
void fn_1_4F14(int no)
{
    M569_PLAYER *player = lbl_1_bss_F8[no]->data;

    player->unk050 = lbl_1_data_1D4[player->unk02C];
    player->unk05C.x = 0.0f;
    player->unk05C.y = 180.0 * (atan2(lbl_1_bss_34.pos.x - player->unk050.x, lbl_1_bss_34.pos.z - player->unk050.z) / M_PI);
    if (player->unk05C.y < 0.0f) {
        player->unk05C.y += 360.0f;
    }
    player->unk05C.z = 0.0f;
    player->mode = 4;
    fn_1_4B8C(lbl_1_bss_F8[no], 2);
}

/* 112 insns: solo player walks under its block. */
void fn_1_5138(int no)
{
    M569_PLAYER *player = lbl_1_bss_F8[no]->data;

    player->unk050 = lbl_1_data_32C[player->unk046];
    player->unk050.y = 0.0f;
    player->unk05C.x = 0.0f;
    player->unk05C.y = 0.0f;
    player->unk05C.z = 0.0f;
    player->mode = 4;
    fn_1_4B8C(lbl_1_bss_F8[no], 2);
}

/* 108 insns: walk to the line-up position. */
void fn_1_52F8(int no)
{
    M569_PLAYER *player = lbl_1_bss_F8[no]->data;

    player->unk050 = lbl_1_data_204[player->unk02C];
    player->unk05C.x = 0.0f;
    player->unk05C.y = 0.0f;
    player->unk05C.z = 0.0f;
    player->mode = 4;
    fn_1_4B8C(lbl_1_bss_F8[no], 2);
}

/* 225 insns: the result motions for one side. */
void fn_1_54A8(int round)
{
    int win = lbl_1_bss_D8[round].unk000;
    int i;
    int no;
    M569_PLAYER *player;

    for (i = 0; i < 3; i++) {
        no = lbl_1_bss_D8[round].unk004[i];
        if (no == -1) {
            continue;
        }
        if (win > 0) {
            fn_1_4B8C(lbl_1_bss_F8[no], 6);
        } else {
            player = lbl_1_bss_F8[no]->data; /* dead; the original has it (a stack store at 0x5694) */
            fn_1_4B8C(lbl_1_bss_F8[no], 7);
        }
    }
}
