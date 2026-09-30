/*
 * m565dll player.c -- written 2026-09-23 (W1 forks; see NOTES.md). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m565dll/asm/REL/m565dll/player.s.
 */

#include "REL/m565dll.h"

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

/* fn_1_8024 inlines MSL's sqrtf algorithm, but the reference pools 0.5 and 3.0 as
 * ordinary literals after the floats (0x208, 0x210): it is not libc/math.h's copy,
 * whose `static const double _half/_three` would be emitted as extra .rodata. The
 * host uses the real sqrtf. */
static inline float PlayerSqrtF(float x)
{
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        y = (float)(x * guess);
        return y;
    }
    return x;
}

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x1D0 */ /* float lbl_1_rodata_1D0 = 150.0f; */
/* 0x1D4 */ /* float lbl_1_rodata_1D4 = 40.0f; */
/* 0x1D8 */ /* float lbl_1_rodata_1D8 = 0.0f; */
/* 0x1DC */ /* float lbl_1_rodata_1DC = 2.0f; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = -300.0f; */
/* 0x1E4 */ /* float lbl_1_rodata_1E4 = 4.0f; */
/* 0x1E8 */ /* float lbl_1_rodata_1E8 = 100.0f; */
/* 0x1EC */ /* float lbl_1_rodata_1EC = 1.5f; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = -225.0f; */
/* 0x1F4 */ /* float lbl_1_rodata_1F4 = 0.2f; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = -9999.99f; */
/* 0x1FC */ /* float lbl_1_rodata_1FC = 1000000000.0f; */
/* 0x200 */ /* float lbl_1_rodata_200 = 10000000000.0f; */
/* 0x208 */ /* double lbl_1_rodata_208 = 0.5; */
/* 0x210 */ /* double lbl_1_rodata_210 = 3; */
/* 0x218 */ /* float lbl_1_rodata_218[2] = { 45.0f, 0.0f }; */

/* --- .data --- */
/* 0x9B8 */ s32 lbl_1_data_9B8[13][7] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C001A, 0x008C002B, 0x008C0030, 0x008C0031, 0x00330000, 0x00330001, 0x00330002, 0x0033001A, 0x0033002B, 0x00330030, 0x00330031, 0x00B70000, 0x00B70001, 0x00B70002, 0x00B7001A, 0x00B7002B, 0x00B70030, 0x00B70031, 0x00ED0000, 0x00ED0001, 0x00ED0002, 0x00ED001A, 0x00ED002B, 0x00ED0030, 0x00ED0031, 0x00E60000, 0x00E60001, 0x00E60002, 0x00E6001A, 0x00E6002B, 0x00E60030, 0x00E60031, 0x00170000, 0x00170001, 0x00170002, 0x0017001A, 0x0017002B, 0x00170030, 0x00170031, 0x00E00000, 0x00E00001, 0x00E00002, 0x00E0001A, 0x00E0002B, 0x00E00030, 0x00E00031, 0x002D0000, 0x002D0001, 0x002D0002, 0x002D001A, 0x002D002B, 0x002D0030, 0x002D0031, 0x00C90000, 0x00C90001, 0x00C90002, 0x00C9001A, 0x00C9002B, 0x00C90030, 0x00C90031, 0x00B00000, 0x00B00001, 0x00B00002, 0x00B0001A, 0x00B0002B, 0x00B00030, 0x00B00031, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C001A, 0x008C002B, 0x008C0030, 0x008C0031, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C001A, 0x008C002B, 0x008C0030, 0x008C0031, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C001A, 0x008C002B, 0x008C0030, 0x008C0031 }; /* [charNo][motion]; dtk's 92nd word is .data alignment */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7820 */ MGPLAYER *lbl_1_bss_7820[4]; /* MgPlayerCreate result per playerNo */

/* --- functions (reference order) --- */
/* 180 insns */
void fn_1_78BC(M565_PLAYER *player, s32 playerNo, M565_OBJECT *obj)
{
    MGACTOR_PARAM param;
    s32 i;
    HU3DMODELID modelId;

    memset(player, 0, sizeof(M565_PLAYER));
    player->unk000 = obj;
    player->unk008 = playerNo;
    player->unk00C = GwPlayerConf[player->unk008].charNo;
    player->unk090 = 0;
    player->unk094 = 0;
    fn_1_9EAC(&player->unk020, player);
    param.height = 150.0f;
    param.radius = 40.0f;
    param.param = playerNo;
    param.type = 0;
    param.attr = 0;
    param.narrowHook = NULL;
    param.correctHook = NULL;
    param.correctHookParam = 0;
    player->unk004 = lbl_1_bss_7820[playerNo] = MgPlayerCreate(playerNo, &param, 8, 1, ~MGPLAYER_ACTFLAG_HIPDROP, NULL);
    player->unk010 = player->unk004->actor->mdlId;
    player->unk074 = &Hu3DData[player->unk010].pos;
    player->unk078 = &Hu3DData[player->unk010].rot;
    for (i = 0; i < 7; i++) {
        player->unk012[i] = CharMotionCreate(player->unk00C, lbl_1_data_9B8[player->unk00C][i]);
    }
    Hu3DModelShadowSet(player->unk010);
    player->unk0A0 = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(0x780073, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 2.0f, 2.0f, 2.0f);
    Hu3DModelCameraSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 5);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    player->unk0A2 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(0x78007D, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, player->unk0A2);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    MgPlayerVibrateCreate(player->unk004);
}

/* 20 insns */
void fn_1_7B8C(M565_PLAYER *player)
{
    Hu3DMotionKill(player->unk0A2);
    Hu3DModelKill(player->unk0A0);
    fn_1_9FF4(&player->unk020);
    memset(player, 0, sizeof(M565_PLAYER));
}

/* 274 insns */
s32 fn_1_7BDC(M565_PLAYER *player)
{
    s32 i;
    M565_OBJECT *obj = player->unk000;
    M565_STAGE *stage = &obj->unk2E4;
    M565_WORK *work = obj->unk000;
    M565_COM *com = &player->unk020;
    M565_STAGEGRID *blk;
    M565_PLAYER *other;
    M565_PLAYER *nearest;
    float maxTime;
    float minDist;
    float dist;
    HuVecF diff;
    float vol;
    float pan;

    fn_1_8024(player);
    if (player->unk074->y < -300.0f && player->unk090 == 0) {
        fn_1_8984(player, 0);
        Hu3DMotionShiftSet(player->unk010, player->unk012[4], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
        player->unk09C = player->unk004->actor->velY / 100.0f;
        player->unk09C = (player->unk09C > 0.0f) ? 0.0f : player->unk09C;
        Hu3DModelShadowReset(player->unk010);
        player->unk090 = 1;
    }
    if (player->unk090 != 0) {
        player->unk09C -= 1.5f;
        if (player->unk09C < -225.0f) {
            player->unk09C = -225.0f;
        }
        player->unk074->y += player->unk09C;
        blk = &stage->unk004[player->unk08A][player->unk088];
        if (blk->unk004 == 102 && blk->unk024 > player->unk074->y) {
            blk->unk024 = blk->unk024 + 0.2f * (player->unk074->y - blk->unk024);
        }
        if (player->unk074->y < -9999.99f) {
            player->unk004->actor->pos.y = player->unk074->y = -9999.99f;
        }
    }
    if (com->unk004 != 0 && player->unk090 == 0) {
        fn_1_A050(com);
        MgPlayerPadSet(player->unk004, com->unk048, com->unk04C, com->unk044, com->unk050);
    }
    if (player->unk094 == 0 || player->unk090 != 0) {
        MgPlayerPadSet(player->unk004, 0, 0, 0, 0);
    }
    if (player->unk0A4 != 0) {
        maxTime = Hu3DMotionMaxTimeGet(player->unk0A0);
        if (Hu3DMotionTimeGet(player->unk0A0) >= maxTime) {
            Hu3DModelAttrSet(player->unk0A0, HU3D_ATTR_DISPOFF);
            player->unk0A4 = 0;
        }
    }
    nearest = NULL;
    minDist = 1000000000.0f;
    for (i = 0; i < 4; i++) {
        other = &obj->unk008[i];
        if (other != player && other->unk090 == 0 && player->unk090 == 0) {
            PSVECSubtract(other->unk074, player->unk074, &diff);
            diff.y = 0.0f;
            dist = PSVECMag(&diff);
            dist = (dist < 0.0f) ? 0.0f : dist;
            if (dist < minDist) {
                minDist = dist;
                nearest = other;
            }
        }
    }
    player->unk080 = nearest;
    player->unk084 = nearest ? minDist : 0.0f;
    fn_1_A10(player->unk074, &vol, &pan);
    if (work->unk3870 != 0) {
        CharModelVoiceVolSet(player->unk00C, vol);
    }
    CharModelVoicePanSet(player->unk00C, pan);
    return 0;
}

/* One neighbour of the player's current block: record its column/row and the squared XZ
 * distance to its centre. Out-of-grid neighbours keep the -9999.99 sentinel. */
#define PLAYER_BLOCK_DIST(n, c, r)                                                    \
    if ((c) >= 0 && (c) < 10 && (r) >= 0 && (r) < 10) {                               \
        col[n] = (c);                                                                 \
        row[n] = (r);                                                                 \
        center = stage->unk004[r][c].unk018;                                          \
        dist[n] = (pos.x - center.x) * (pos.x - center.x) + (pos.z - center.z) * (pos.z - center.z); \
    }

/* 600 insns */
void fn_1_8024(M565_PLAYER *player)
{
    M565_OBJECT *obj = player->unk000;
    M565_STAGE *stage = &obj->unk2E4;
    float dist[9];
    s16 col[9];
    s16 row[9];
    HuVecF pos;
    HuVecF center;
    s32 best;
    s32 i;
    float bestDist;
    float d;

    pos.x = player->unk074->x;
    pos.y = 0.0f;
    pos.z = player->unk074->z;
    dist[0] = dist[1] = dist[2] = dist[3] = dist[4] = dist[5] = dist[6] = dist[7] = dist[8] = -9999.99f;
    PLAYER_BLOCK_DIST(0, player->unk088, player->unk08A)
    PLAYER_BLOCK_DIST(1, player->unk088, player->unk08A - 1)
    PLAYER_BLOCK_DIST(2, player->unk088 + 1, player->unk08A - 1)
    PLAYER_BLOCK_DIST(3, player->unk088 + 1, player->unk08A)
    PLAYER_BLOCK_DIST(4, player->unk088 + 1, player->unk08A + 1)
    PLAYER_BLOCK_DIST(5, player->unk088, player->unk08A + 1)
    PLAYER_BLOCK_DIST(6, player->unk088 - 1, player->unk08A + 1)
    PLAYER_BLOCK_DIST(7, player->unk088 - 1, player->unk08A)
    PLAYER_BLOCK_DIST(8, player->unk088 - 1, player->unk08A - 1)
    best = 0;
    bestDist = 10000000000.0f;
    for (i = 0; i < 9; i++) {
        if (dist[i] >= 0.0f && dist[i] < bestDist) {
            best = i;
            bestDist = dist[i];
        }
    }
    player->unk088 = col[best];
    player->unk08A = row[best];
    d = dist[best];
    player->unk08C = PlayerSqrtF(d);
}

/* 20 insns */
void fn_1_8984(M565_PLAYER *player, s32 on)
{
    if (on) {
        MgPlayerPauseOff(player->unk004, player->unk074);
    } else {
        MgPlayerPauseOn(player->unk004);
    }
}

/* 63 insns */
void fn_1_89D4(M565_PLAYER *player, float angle, s32 knockback)
{
    HU3DMODELID modelId;

    if (knockback) {
        MgPlayerStunSet(player->unk004, MGPLAYER_STUN_KNOCKBACK, angle, -1);
    } else {
        MgPlayerStunSet(player->unk004, MGPLAYER_STUN_HIT, angle, -1);
    }
    if (player->unk0A4 == 0) {
        modelId = player->unk0A0;
        Hu3DModelPosSet(modelId, player->unk074->x, player->unk074->y, player->unk074->z);
        Hu3DModelRotSet(modelId, 45.0f, angle, 0.0f);
        Hu3DMotionTimeSet(modelId, 0.0f);
        Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
        player->unk0A4 = 1;
    }
}
