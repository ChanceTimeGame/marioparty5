/*
 * m510dll player.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/player.s.
 */

#include "REL/m510dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x98 */ /* float lbl_1_rodata_98 = -250.0f; */
/* 0x9C */ /* float lbl_1_rodata_9C = 130.0f; */
/* 0xA0 */ /* float lbl_1_rodata_A0 = 1300.0f; */
/* 0xA4 */ /* float lbl_1_rodata_A4 = 0.0f; */
/* 0xA8 */ /* float lbl_1_rodata_A8 = 8.0f; */
/* 0xAC */ /* float lbl_1_rodata_AC = 2.5f; */

/* --- .data --- */
/* 0x110 */ HuVecF lbl_1_data_110[4] = { { 0.0f, 0.0f, 0.0f }, { 300.0f, 0.0f, 0.0f }, { 600.0f, 0.0f, 0.0f }, { 900.0f, 0.0f, 0.0f } };

/* --- functions (reference order) --- */
/* 154 insns */
void fn_1_3A64(M510_PLAYER *player, s16 playerNo, M510_WORK *work)
{
    M510_WORK *w = work;
    M510_CAMERA *camera = &w->unk2474;
    HU3DMODELID modelId;
    HuVecF pos;

    memset(player, 0, sizeof(M510_PLAYER));
    player->unk000 = work;
    player->unk004 = playerNo;
    fn_1_47C4(&player->unk118, player);
    player->unk118.unk010 = lbl_1_data_110[playerNo];
    player->unk118.unk010.z += -250.0f;
    fn_1_509C(&player->unk154, player);
    fn_1_3DC8(&player->unk008, playerNo, player);
    fn_1_CE04(&player->unk850, 0, playerNo);
    pos = lbl_1_data_110[playerNo];
    pos.x -= 130.0f;
    pos.z = 1300.0f;
    player->unk008.unk0B8 = pos;
    CharEffectLayerSet(4);
    player->unk878 = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(0x44000E, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(modelId, 8.0f, 8.0f, 8.0f);
    player->unk87A = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(0x44001F, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, player->unk87A);
    Hu3DMotionSpeedSet(modelId, 2.5f);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
}

/* 26 insns */
void fn_1_3CCC(M510_PLAYER *player)
{
    Hu3DMotionKill(player->unk87A);
    Hu3DModelKill(player->unk878);
    fn_1_D1AC(&player->unk850);
    fn_1_4284(&player->unk008);
    fn_1_51B4(&player->unk154);
    fn_1_49A4(&player->unk118);
    memset(player, 0, sizeof(M510_PLAYER));
}

/* 37 insns */
s32 fn_1_3D34(M510_PLAYER *player)
{
    float maxTime;

    fn_1_49F4(&player->unk118);
    fn_1_4328(&player->unk008);
    fn_1_D234(&player->unk850);
    fn_1_5230(&player->unk154);
    if (player->unk87C != 0) {
        maxTime = Hu3DMotionMaxTimeGet(player->unk878);
        if (Hu3DMotionTimeGet(player->unk878) >= maxTime) {
            Hu3DModelAttrSet(player->unk878, HU3D_ATTR_DISPOFF);
            player->unk87C = 0;
        }
    }
    return 0;
}
