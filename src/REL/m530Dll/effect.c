/*
 * m530Dll effect.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m530Dll/asm/REL/m530Dll/effect.s.
 */

#include "REL/m530Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/hu3d.h"
#include "game/object.h"
#include "datadir_enum.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x1C0 */ /* float lbl_1_rodata_1C0 = 0.0f; */
/* 0x1C4 */ /* float lbl_1_rodata_1C4 = 100.0f; */
/* 0x1C8 */ /* float lbl_1_rodata_1C8 = 10.0f; */
/* 0x1CC */ /* float lbl_1_rodata_1CC = 0.26785713f; */
/* 0x1D0 */ /* double lbl_1_rodata_1D0 = 4503601774854144; */
/* 0x1D8 */ /* double lbl_1_rodata_1D8 = 7.5; */
/* 0x1E0 */ /* double lbl_1_rodata_1E0 = 180; */
/* 0x1E8 */ /* double lbl_1_rodata_1E8 = 3.141592653589793; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = 30.0f; */
/* 0x1F4 */ /* float lbl_1_rodata_1F4 = 120.0f; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = 550.0f; */
/* 0x1FC */ /* float lbl_1_rodata_1FC = 60.0f; */
/* 0x200 */ /* float lbl_1_rodata_200 = 7.5f; */
/* 0x204 */ /* s32 lbl_1_rodata_204[4] = { 0x00000078, 0x0000003C, 0x00000028, 0x0000001E }; */
/* 0x214 */ /* float lbl_1_rodata_214 = 15.0f; */

/* --- .data --- */
/* 0x390 */ s32 lbl_1_data_390[3] = { 0x00000003, 0x00000004, 0x00000005 };

/* --- functions (reference order) --- */
/* 45 insns. Spawn a one-shot effect model (m530 #7) at the pitch centre. */
void fn_1_8848(void)
{
    HU3DMODELID modelId;
    OMOBJ *obj;

    modelId = Hu3DModelCreateData(DATANUM(DATA_m530, 7));
    obj = omAddObjEx(lbl_1_bss_B8, 0x3000, 1, 0, OM_GRP_NONE, fn_1_88FC);
    obj->mdlId[0] = modelId;
    Hu3DModelLayerSet(modelId, 1);
    omSetTra(obj, 0.0f, 100.0f, lbl_1_data_348[0].z);
}

/* 23 insns. = m523 player.c fn_1_4534: kill when the motion ends. */
void fn_1_88FC(OMOBJ *obj)
{
    if (Hu3DMotionEndCheck(obj->mdlId[0])) {
        Hu3DModelKill(obj->mdlId[0]);
        omDelObjEx(lbl_1_bss_B8, obj);
    }
}

/* 182 insns. Player main (objFunc installed by player.c). */
void fn_1_8958(OMOBJ *obj)
{
    M530_PLAYER *player;
    s16 vol;
    s16 pan;

    player = obj->data;
    fn_1_1A50(&player->pos, &vol, &pan);
    CharModelVoicePanSet(player->charNo, pan);
    CharModelVoiceVolSet(player->charNo, vol);
    if (MgSeqModeGet() == 6) {
        CharModelAttrReset(player->charNo, 1);
        player->unk038 = 0;
        player->mode = 3;
        obj->objFunc = fn_1_916C;
    }
    else if (MgSeqModeGet() == 5) {
        switch (player->mode) {
            case 1:
                if (player->unk038 == 0) {
                    omVibrate(player->no, 12, 12, 0);
                    fn_1_10E8(obj, 8);
                }
                player->unk038++;
                if (CharMotionEndCheck(player->charNo)) {
                    player->unk038 = 0;
                    fn_1_10E8(obj, 3);
                    player->mode = 0;
                }
                break;
            case 2:
                if (player->unk038 == 0) {
                    fn_1_10E8(obj, 3);
                }
                player->unk038++;
                if (player->unk038 % 2) {
                    CharModelAttrSet(player->charNo, 1);
                }
                else {
                    CharModelAttrReset(player->charNo, 1);
                }
                if (player->unk038 == 30) {
                    player->unk038 = 0;
                    player->mode = 0;
                }
                break;
        }
        player->unk078.x = 0.0f;
        player->unk078.y = 0.0f;
        player->unk078.z = 0.0f;
        if (player->comF) {
            fn_1_9388(obj);
        }
        else if (fn_1_342C(player->padNo) >= 10.0f) {
            player->unk078.x = 0.26785713f * HuPadStkX[player->padNo];
            player->unk078.z = 0.26785713f * -HuPadStkY[player->padNo];
        }
        fn_1_8C30(obj);
        omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
        omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    }
}

/* 127 insns. Move by the velocity, pick the motion, collect kinomi. */
void fn_1_8C30(OMOBJ *obj)
{
    M530_PLAYER *player;
    s32 motion;
    HuVecF pos;

    player = obj->data;
    if (player->mode != 1) {
        if (fabs(player->unk078.x) > 7.5 || fabs(player->unk078.z) > 7.5) {
            motion = 2;
        }
        else if (PSVECMag(&player->unk078) == 0.0f) {
            motion = 0;
        }
        else {
            motion = 1;
        }
        if (motion != player->unk074) {
            fn_1_10E8(obj, lbl_1_data_390[motion]);
        }
        if (PSVECMag(&player->unk078) != 0.0f) {
            player->unk084 = 180.0 * (atan2(player->unk078.x, player->unk078.z) / M_PI);
            PSVECAdd(&player->pos, &player->unk078, &pos);
            fn_1_8E2C(player, &pos);
            fn_1_8ED8(&pos);
            player->pos = pos;
        }
        if (player->mode != 2) {
            fn_1_8F64(obj);
        }
        player->rot.y = fn_1_3FF4(player->rot.y, player->unk084, 30.0f);
    }
}

/* 43 insns. Push pos out of the other active players (radius 120). */
s32 fn_1_8E2C(M530_PLAYER *player, HuVecF *pos)
{
    s32 i;
    M530_PLAYER *other;

    for (i = 0; i < 4; i++) {
        other = lbl_1_bss_40[i]->data;
        if (player != other && other->unk02C) {
            if (fn_1_4164(&player->pos, pos, &other->pos, 120.0f)) {
                return 1;
            }
        }
    }
    return 0;
}

/* 35 insns. Clamp pos to the 550 circle. */
s32 fn_1_8ED8(HuVecF *pos)
{
    float mag;

    mag = PSVECMag(pos);
    if (mag <= 550.0f) {
        return 0;
    }
    PSVECNormalize(pos, pos);
    PSVECScale(pos, pos, 550.0f);
    return 1;
}

/* 130 insns. Catch a falling kinomi / get hit. */
void fn_1_8F64(OMOBJ *obj)
{
    M530_PLAYER *player;
    s32 idx;
    HuVecF pos;

    player = obj->data;
    idx = fn_1_65D4(&player->pos, 100.0f);
    if (idx != -1 && lbl_1_bss_DC[idx].unk03C == 5) {
        if (lbl_1_bss_DC[idx].unk040 == 4) {
            if (lbl_1_bss_DC[idx].unk044 == 0) {
                fn_1_1B78(&player->pos, 0x79D);
                lbl_1_bss_4C[player->grp].unk008 += 1;
            }
            else {
                fn_1_1B78(&player->pos, 0x79E);
                lbl_1_bss_4C[player->grp].unk008 += 3;
            }
            omVibrate(player->no, 12, 6, 6);
            Hu3DModelObjPosGet(obj->mdlId[0], player->unk034, &pos);
            CharEffectCoinGlowCreate(lbl_1_data_6C.no, &pos);
            fn_1_1648(player->grp);
            fn_1_694C(idx);
            return;
        }
        if (lbl_1_bss_DC[idx].unk040 == 6) {
            fn_1_1B78(&player->pos, 0x79F);
            player->mode = 1;
            player->unk038 = 0;
            fn_1_694C(idx);
            return;
        }
    }
    idx = fn_1_645C(&player->pos, 60.0f);
    if (idx != -1 && lbl_1_bss_DC[idx].unk03C == 7) {
        fn_1_1B78(&player->pos, 0x79F);
        player->mode = 1;
        player->unk038 = 0;
        fn_1_6980(idx);
        return;
    }
}

/* 35 insns. Finish: dust, then walk home after 60 frames. */
void fn_1_916C(OMOBJ *obj)
{
    M530_PLAYER *player;

    player = obj->data;
    if (player->unk038 == 0) {
        CharModelHookDustCreate(player->charNo, player->unk034);
        fn_1_10E8(obj, 0);
    }
    player->unk038++;
    if (player->unk038 == 60) {
        player->unk038 = 0;
        player->mode = 4;
        obj->objFunc = fn_1_91F8;
    }
}

/* 60 insns. Walk to the team's home position. */
void fn_1_91F8(OMOBJ *obj)
{
    M530_PLAYER *player;

    player = obj->data;
    if (player->unk038++ == 0) {
        fn_1_10E8(obj, 2);
        player->unk088 = 1;
        player->unk08C = lbl_1_data_360[player->grp];
        player->unk098 = 7.5f;
    }
    else {
        if (fn_1_96F8(obj)) {
            player->unk038 = 0;
            player->mode = 5;
            obj->objFunc = fn_1_92E8;
        }
        omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
        omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    }
}

/* 39 insns. Turn to face the camera, then idle. */
void fn_1_92E8(OMOBJ *obj)
{
    M530_PLAYER *player;

    player = obj->data;
    player->rot.y = fn_1_3FF4(player->rot.y, 0.0f, 30.0f);
    omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
    if ((s32)player->rot.y == 0) {
        fn_1_10E8(obj, 0);
        obj->objFunc = fn_1_9384;
    }
}

/* 1 insns */
void fn_1_9384(OMOBJ *obj) { }

/* 54 insns. COM brain. */
void fn_1_9388(OMOBJ *obj)
{
    M530_PLAYER *player;

    player = obj->data;
    if (player->unk044 != -1) {
        if (lbl_1_bss_DC[player->unk044].unk03C < 2) {
            player->unk03C = 0;
        }
        if (lbl_1_bss_DC[player->unk044].unk03C >= 6) {
            player->unk03C = 0;
        }
    }
    switch (player->unk03C) {
        case 0:
            fn_1_9460(obj);
            break;
        case 1:
            fn_1_95B0(obj);
            break;
        case 2:
            fn_1_96B0(obj);
            break;
    }
}

/* 84 insns. COM: pick a kinomi the opposing team is not chasing. */
void fn_1_9460(OMOBJ *obj)
{
    M530_PLAYER *player = obj->data;
    M530_PLAYER *other;
    s32 otherNo;
    s32 idx;
    HuVecF dir;
    s32 waitTbl[4] = { 120, 60, 40, 30 };

    if (player->unk040++ > waitTbl[player->dif]) {
        otherNo = lbl_1_bss_4C[player->grp ^ 1].unk000[1];
        other = lbl_1_bss_40[otherNo]->data;
        idx = fn_1_6C50(player->dif, other->unk044);
        if (idx != -1) {
            player->unk040 = 0;
            player->unk044 = idx;
            player->unk048 = lbl_1_bss_DC[idx].unk004;
            player->unk048.y = 0.0f;
            PSVECSubtract(&player->unk048, &player->pos, &dir);
            if ((s32)PSVECMag(&dir) == 0) {
                player->unk03C = 2;
            }
            else {
                player->unk03C = 1;
            }
        }
    }
}

/* 64 insns. COM: walk to the target at 15. */
void fn_1_95B0(OMOBJ *obj)
{
    M530_PLAYER *player;
    float mag;
    HuVecF dir;

    player = obj->data;
    PSVECSubtract(&player->unk048, &player->pos, &dir);
    mag = PSVECMag(&dir);
    if ((s32)mag == 0) {
        player->unk03C = 2;
        return;
    }
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, &dir, 15.0f);
    if (PSVECMag(&dir) > mag) {
        player->unk078.x = 0.0f;
        player->unk078.y = 0.0f;
        player->unk078.z = 0.0f;
    }
    else {
        player->unk078 = dir;
    }
}

/* 18 insns. COM: wait until the target kinomi is gone. */
void fn_1_96B0(OMOBJ *obj)
{
    M530_PLAYER *player;

    player = obj->data;
    if (lbl_1_bss_DC[player->unk044].unk03C == 0) {
        player->unk044 = -1;
        player->unk03C = 0;
    }
}

/* 105 insns. Step toward unk08C; returns 1 on arrival. */
s32 fn_1_96F8(OMOBJ *obj)
{
    M530_PLAYER *player;
    M530_PLAYER *other;
    s32 i;
    float mag;
    HuVecF pos;
    HuVecF dir;

    player = obj->data;
    PSVECSubtract(&player->unk08C, &player->pos, &dir);
    mag = PSVECMag(&dir);
    if (0.0f == mag) {
        return 1;
    }
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, &dir, player->unk098);
    if (PSVECMag(&dir) > mag) {
        player->pos = player->unk08C;
        player->unk088 = 0;
        return 1;
    }
    PSVECAdd(&player->pos, &dir, &pos);
    for (i = 0; i < 4; i++) {
        other = lbl_1_bss_40[i]->data;
        if (player != other && other->unk02C) {
            if (fn_1_4164(&player->pos, &pos, &other->pos, 120.0f)) {
                break;
            }
        }
    }
    player->pos = pos;
    player->rot.y = 180.0 * (atan2(dir.x, dir.z) / M_PI);
    return 0;
}
