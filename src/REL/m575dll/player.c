/*
 * m575dll player.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/player.s.
 */

#include "REL/m575dll.h"

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
#include "string.h"

/* retail passes the camera word unnarrowed (lwz, no extsh): no prototype in scope */
void Hu3D3Dto2D();

/* actman.h does not declare MgActorPosGet */
void MgActorPosGet(MGACTOR *actorP, HuVecF *pos);

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x1C0 */ /* s32 lbl_1_rodata_1C0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1CC */ /* float lbl_1_rodata_1CC = 150.0f; */
/* 0x1D0 */ /* float lbl_1_rodata_1D0 = 40.0f; */
/* 0x1D4 */ /* float lbl_1_rodata_1D4 = -150.0f; */
/* 0x1D8 */ /* float lbl_1_rodata_1D8 = -1.0f; */
/* 0x1DC */ /* float lbl_1_rodata_1DC = 0.0f; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = 0.6f; */
/* 0x1E4 */ /* float lbl_1_rodata_1E4 = 0.4f; */
/* 0x1E8 */ /* float lbl_1_rodata_1E8 = 0.8f; */
/* 0x1EC */ /* float lbl_1_rodata_1EC = -25.0f; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = 4.0f; */
/* 0x1F4 */ /* float lbl_1_rodata_1F4 = 100.0f; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = 1.5f; */
/* 0x1FC */ /* float lbl_1_rodata_1FC = -225.0f; */
/* 0x200 */ /* float lbl_1_rodata_200 = -3000.0f; */
/* 0x204 */ /* float lbl_1_rodata_204 = 2.0f; */
/* 0x208 */ /* float lbl_1_rodata_208 = 576.0f; */
/* 0x20C */ /* float lbl_1_rodata_20C = 0.5f; */
/* 0x210 */ /* float lbl_1_rodata_210 = 48.0f; */
/* 0x214 */ /* float lbl_1_rodata_214 = 16.0f; */
/* 0x218 */ /* float lbl_1_rodata_218 = 80.0f; */
/* 0x21C */ /* float lbl_1_rodata_21C = 30.0f; */
/* 0x220 */ /* float lbl_1_rodata_220 = 1.0f; */
/* 0x224 */ /* float lbl_1_rodata_224 = 0.3f; */
/* 0x228 */ /* float lbl_1_rodata_228 = 400.0f; */
/* 0x22C */ /* float lbl_1_rodata_22C = 0.1f; */
/* 0x230 */ /* float lbl_1_rodata_230 = 0.2f; */
/* 0x234 */ /* float lbl_1_rodata_234 = 0.7f; */
/* 0x238 */ /* float lbl_1_rodata_238 = -0.0001f; */
/* 0x23C */ /* float lbl_1_rodata_23C = 25.0f; */
/* 0x240 */ /* float lbl_1_rodata_240 = 5.0f; */
/* 0x248 */ /* double lbl_1_rodata_248 = 0.001; */
/* 0x250 */ /* float lbl_1_rodata_250[2] = { 2000.0f, 0.0f }; */

/* --- .data --- */
/* 0x58 */ MGPLAYER_MODE_FUNC lbl_1_data_58[18] = { fn_1_61CC, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
/* 0xA0 */ s32 lbl_1_data_A0[118] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0003, 0x008C0004, 0x008C002B, 0x008C005A, 0x008C0006, 0x008C0007, 0x00330000, 0x00330001, 0x00330002, 0x00330003, 0x00330004, 0x0033002B, 0x0033005A, 0x00330006, 0x00330007, 0x00B70000, 0x00B70001, 0x00B70002, 0x00B70003, 0x00B70004, 0x00B7002B, 0x00B7005A, 0x00B70006, 0x00B70007, 0x00ED0000, 0x00ED0001, 0x00ED0002, 0x00ED0003, 0x00ED0004, 0x00ED002B, 0x00ED005A, 0x00ED0006, 0x00ED0007, 0x00E60000, 0x00E60001, 0x00E60002, 0x00E60003, 0x00E60004, 0x00E6002B, 0x00E6005A, 0x00E60006, 0x00E60007, 0x00170000, 0x00170001, 0x00170002, 0x00170003, 0x00170004, 0x0017002B, 0x0017005A, 0x00170006, 0x00170007, 0x00E00000, 0x00E00001, 0x00E00002, 0x00E00003, 0x00E00004, 0x00E0002B, 0x00E0005A, 0x00E00006, 0x00E00007, 0x002D0000, 0x002D0001, 0x002D0002, 0x002D0003, 0x002D0004, 0x002D002B, 0x002D005A, 0x002D0006, 0x002D0007, 0x00C90000, 0x00C90001, 0x00C90002, 0x00C90003, 0x00C90004, 0x00C9002B, 0x00C9005A, 0x00C90006, 0x00C90007, 0x00B00000, 0x00B00001, 0x00B00002, 0x00B00003, 0x00B00004, 0x00B0002B, 0x00B0005A, 0x00B00006, 0x00B00007, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0003, 0x008C0004, 0x008C002B, 0x008C005A, 0x008C0006, 0x008C0007, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0003, 0x008C0004, 0x008C002B, 0x008C005A, 0x008C0006, 0x008C0007, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0003, 0x008C0004, 0x008C002B, 0x008C005A, 0x008C0006, 0x008C0007, 0x00000000 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7810 */ M575_PLAYER *lbl_1_bss_7810[4]; /* per player no (fn_1_535C) */

/* --- functions (reference order) --- */

/* player fn_1_535C, 164 insns. Player init. */
void fn_1_535C(M575_PLAYER *player, s16 side, s16 playerNo, M575_TEAM *team)
{
    MGACTOR_PARAM param;
    s32 i;
    M575_CAMERA *camera;

    camera = &team->unkE20;
    memset(player, 0, sizeof(M575_PLAYER));
    player->unk000 = team;
    player->unk00C = side;
    player->unk00E = playerNo;
    player->unk010 = GwPlayerConf[player->unk00E].charNo;
    player->unk0A4 = 0;
    player->unk028 = CharModelHeightGet(player->unk010);
    player->unk094 = 150.0f;
    lbl_1_bss_7810[playerNo] = player;
    param.height = 150.0f;
    param.radius = 40.0f;
    param.param = player->unk00E;
    param.type = 0;
    param.attr = 0;
    param.narrowHook = fn_1_5FC8;
    param.correctHook = fn_1_5CD8;
    /* retail stores the player pointer in an int */
    param.correctHookParam = (int)player;
    player->unk008 = MgPlayerCreate(player->unk00E, &param, 4, camera->unk004, 3, NULL);
    player->unk014 = player->unk008->actor->mdlId;
    player->unk078 = &Hu3DData[player->unk014].pos;
    player->unk07C = &Hu3DData[player->unk014].rot;
    Hu3DModelCameraSet(player->unk014, camera->unk004);
    for (i = 0; i < 9; i++) {
        player->unk016[i] = CharMotionCreate(player->unk010, ((s32 (*)[9])lbl_1_data_A0)[player->unk010][i]);
    }
    MgPlayerModeFuncSet(player->unk008, lbl_1_data_58);
    Hu3DModelShadowSet(player->unk014);
    {
        HuVecF zero = { 0.0f, 0.0f, 0.0f };
        HuVecF *src = &zero;
        *player->unk078 = *src;
    }
    player->unk078->x = (side & 1) ? 150.0f : -150.0f;
    MgActorPosSet(player->unk008->actor, player->unk078);
    fn_1_6630(&player->unk02C, player);
}

/* player fn_1_55EC, 16 insns. Player close. */
void fn_1_55EC(M575_PLAYER *player)
{
    fn_1_675C(&player->unk02C);
    memset(player, 0, sizeof(M575_PLAYER));
}

/* player fn_1_562C, 407 insns. Player frame. */
s32 fn_1_562C(M575_PLAYER *player)
{
    Mtx mtx;
    HuVecF pos;
    HuVecF push;
    HuVecF scr;
    float pan;
    M575_TUBOEFF *eff;
    M575_PLAYER *partner;
    M575_WORK *work;
    M575_TEN *ten;
    M575_JUGEM *jugem;
    M575_TEAM *team;
    M575_COM *com;

    team = player->unk000;
    ten = &team->unk1A0;
    work = team->unk000;
    com = &player->unk02C;
    jugem = &team->unk1298;
    eff = &ten->unk02C;
    partner = (player == &team->unk008[0]) ? &team->unk008[1] : &team->unk008[0];
    if (com->unk008 != 0) {
        fn_1_678C(com);
        MgPlayerPadSet(player->unk008, com->unk040, com->unk044, com->unk03C, com->unk048);
    }
    if (player->unk0A4 == 0) {
        MgPlayerPadSet(player->unk008, 0, 0, 0, 0);
    }
    if (player->unk008->mode == 1) {
        player->unk0A8 = 1;
    }
    if (player->unk0A8 != 0 && player->unk0AC < 60) {
        player->unk0AC++;
    }
    PSMTXCopy(eff->unk078, mtx);
    PSMTXMultVec(mtx, player->unk078, &pos);
    pos.x *= -1.0f;
    pos.z *= -1.0f;
    PSVECSubtract(&pos, ten->unk008, &pos);
    player->unk088 = pos;
    pos.y = 0.0f;
    player->unk094 = PSVECMag(&pos);
    if (player->unk008->mode == 1 || player->unk008->mode == 2) {
        player->unk0B4 = 1;
    } else {
        player->unk0B4 = 0;
        player->unk0B8 = 0;
    }
    if (player->unk0B4 != 0) {
        if (player->unk0BC >= 0.0f && player->unk008->actor->velY < 0.0f) {
            player->unk0B8 = 1;
        }
    } else {
        player->unk0B8 = 0;
    }
    push = player->unk0C0;
    if (push.x || push.y || push.z) {
        MgActorPosGet(player->unk008->actor, &pos);
        pos.x += 0.6f * push.x;
        pos.y += 0.6f * push.y;
        pos.z += 0.6f * push.z;
        MgActorPosSet(player->unk008->actor, &pos);
        MgActorPosGet(partner->unk008->actor, &pos);
        pos.x -= 0.4f * push.x;
        pos.y -= 0.4f * push.y;
        pos.z -= 0.4f * push.z;
        MgActorPosSet(partner->unk008->actor, &pos);
        PSVECScale(&player->unk0C0, &player->unk0C0, 0.8f);
    }
    if (player->unk088.y < -25.0f && player->unk0B0 == 0) {
        fn_1_5C88(player, 0);
        Hu3DMotionShiftSet(player->unk014, player->unk016[5], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
        player->unk084 = player->unk008->actor->velY / 100.0f;
        player->unk084 = (player->unk084 > 0.0f) ? 0.0f : player->unk084;
        player->unk0B0 = 1;
    }
    if (player->unk088.y < -25.0f && (jugem->unk02C == 0 || jugem->unk028 != player)) {
        Hu3DModelShadowDispOff(player->unk014);
    } else {
        Hu3DModelShadowDispOn(player->unk014);
    }
    if (player->unk0B0 != 0) {
        fn_1_CFE4(jugem, player);
        if (jugem->unk02C == 0 || jugem->unk028 != player) {
            player->unk084 -= 1.5f;
            if (player->unk084 < -225.0f) {
                player->unk084 = -225.0f;
            }
            player->unk078->y += player->unk084;
        }
        if (player->unk078->y < -3000.0f) {
            player->unk078->y = -3000.0f;
        }
    }
    player->unk0BC = player->unk008->actor->velY;
    player->unk0A0++;
    if (work->unk00C >= 4) {
        Hu3D3Dto2D(player->unk078, team->unkE20.unk004, &scr);
        pan = 2.0f * (scr.x / 576.0f - 0.5f);
        /* retail: pan is not clamped; an off-screen player gives < 0 or > 127 */
        pan = (team->unk004 == 0) ? 48.0f + 16.0f * pan : 80.0f + 16.0f * pan;
        CharModelVoicePanSet(player->unk010, pan);
    } else {
        CharModelVoicePanSet(player->unk010, 64);
    }
    return 0;
}

/* player fn_1_5C88, 20 insns. Pause (0) / resume (1) the player's actor. */
void fn_1_5C88(M575_PLAYER *player, s32 on)
{
    if (on) {
        MgPlayerPauseOff(player->unk008, player->unk078);
    } else {
        MgPlayerPauseOn(player->unk008);
    }
}

/* player fn_1_5CD8, 188 insns. Actor correct hook: standing on the team's board tips it. */
void fn_1_5CD8(MGACTOR *actor, int param)
{
    HuVecF force;
    float mag;
    float angle;
    float weight;
    float dist;
    M575_TUBOEFF *eff;
    s16 mesh;
    M575_TEN *ten;
    M575_WORK *work;
    M575_TEAM *team;
    M575_PLAYER *player;

    player = (M575_PLAYER *)actor->correctHookParam;
    team = player->unk000;
    work = team->unk000;
    ten = &team->unk1A0;
    eff = &ten->unk02C;
    mesh = actor->colMesh;
    if (work->unk25E0[mesh] == ten->unk010) {
        angle = ten->unk020;
        weight = angle / 30.0f;
        weight = weight * (0.5f + 0.5f * weight);
        weight = (weight > 1.0f) ? 1.0f : ((weight < 0.3f) ? 0.3f : weight);
        mag = PSVECMag(&player->unk088);
        dist = mag / 400.0f;
        dist = (dist > 1.0f) ? 1.0f : ((dist < 0.0f) ? 0.0f : dist);
        dist = (dist < 0.3f) ? 0.1f : ((dist < 0.5f) ? 0.2f : ((dist < 0.7f) ? 0.6f : 1.0f));
        if (work->unk00C < 5) {
            force.x = 0.0f;
            force.y = -0.0001f * weight;
            force.z = 0.0f;
            fn_1_9B58(eff, &force, player->unk078);
            ten->unk01C = 4;
        }
    }
}

/* player fn_1_5FC8, 129 insns. Actor narrow hook: landing on another player's head
   bounces off it. */
int fn_1_5FC8(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b)
{
    HuVecF d;
    M575_WORK *work;
    M575_PLAYER *p0;
    M575_PLAYER *p1;
    M575_PLAYER *p2;
    M575_PLAYER *p3;
    M575_PLAYER *player;
    M575_PLAYER *other;

    work = lbl_1_bss_0;
    p0 = lbl_1_bss_7810[0];
    p1 = lbl_1_bss_7810[1];
    p2 = lbl_1_bss_7810[2];
    p3 = lbl_1_bss_7810[3];
    player = (a->paramB == 0) ? p0 : ((a->paramB == 1) ? p1 : ((a->paramB == 2) ? p2 : p3));
    other = (b->paramB == 0) ? p0 : ((b->paramB == 1) ? p1 : ((b->paramB == 2) ? p2 : p3));
    if (player->unk0B8 != 0 && player->unk008->actor->velY > 0.0f) {
        player->unk008->actor->velY = 0.0f;
        MgPlayerModeSet(player->unk008, 2);
        player->unk008->actor->forceB.x = 0.0f;
        player->unk008->actor->forceB.z = 0.0f;
        player->unk008->actor->rotY = player->unk07C->y;
        PSVECSubtract(player->unk078, other->unk078, &d);
        d.y = 0.0f;
        player->unk0C0.x = 0.2f * d.x;
        player->unk0C0.y = 0.0f;
        player->unk0C0.z = 0.2f * d.z;
    }
    return 1;
}

/* player fn_1_61CC, 281 insns. MgPlayer mode 0 (walk): A jumps, B punches, walk/run
   motions; the board's tilt speeds the motion up. */
void fn_1_61CC(MGPLAYER *playerP)
{
    float speed;
    M575_WORK *work;
    M575_PLAYER *p0;
    M575_PLAYER *p1;
    M575_PLAYER *p2;
    M575_PLAYER *p3;
    M575_PLAYER *player;
    M575_TEAM *team;
    M575_TEN *ten;

    work = lbl_1_bss_0;
    p0 = lbl_1_bss_7810[0];
    p1 = lbl_1_bss_7810[1];
    p2 = lbl_1_bss_7810[2];
    p3 = lbl_1_bss_7810[3];
    player = (p1->unk008 == playerP) ? p1 : ((p2->unk008 == playerP) ? p2 : ((p3->unk008 == playerP) ? p3 : p0));
    team = player->unk000;
    ten = &team->unk1A0;
    if (playerP->actor->colGroundAttr & 0x407F) {
        if (!MgPlayerAttrCheck(playerP, MGPLAYER_ATTR_COMSTK) && (HuPadBtnDown[playerP->padNo] & PAD_BUTTON_A)) {
            if (playerP->actionFlag & MGPLAYER_ACTFLAG_JUMP) {
                MgPlayerModeSet(playerP, MGPLAYER_MODE_JUMP);
            }
        } else if (!MgPlayerAttrCheck(playerP, MGPLAYER_ATTR_COMSTK) && (HuPadBtnDown[playerP->padNo] & PAD_BUTTON_B)) {
            if (playerP->actionFlag & MGPLAYER_ACTFLAG_PUNCH) {
                MgPlayerModeSet(playerP, MGPLAYER_MODE_PUNCH);
            }
        } else if (playerP->actionFlag & MGPLAYER_ACTFLAG_WALK) {
            speed = playerP->actor->vel.x * playerP->actor->vel.x + playerP->actor->vel.z * playerP->actor->vel.z;
            if (speed > 25.0f) {
                if (playerP->motNo != MGPLAYER_MOT_RUN) {
                    CharMotionShiftSet(playerP->charNo, playerP->omObj->mtnId[MGPLAYER_MOT_RUN], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
                    playerP->motNo = MGPLAYER_MOT_RUN;
                }
                if (ten->unk020 > 25.0f) {
                    Hu3DMotionSpeedSet(player->unk014, 2.0f);
                    if (work->unk008 & 1) {
                        CharModelCryCreate(player->unk010, 30.0f, 0.8f);
                    }
                } else {
                    Hu3DMotionSpeedSet(player->unk014, 1.0f);
                }
            } else if (speed > 0.001) {
                if (playerP->motNo != MGPLAYER_MOT_WALK) {
                    CharMotionShiftSet(playerP->charNo, playerP->omObj->mtnId[MGPLAYER_MOT_WALK], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
                    playerP->motNo = MGPLAYER_MOT_WALK;
                }
                if (ten->unk020 > 25.0f) {
                    Hu3DMotionSpeedSet(player->unk014, 2.0f);
                    if (work->unk008 & 1) {
                        CharModelCryCreate(player->unk010, 30.0f, 0.8f);
                    }
                } else {
                    Hu3DMotionSpeedSet(player->unk014, 1.0f);
                }
            } else {
                if (playerP->motNo != MGPLAYER_MOT_IDLE) {
                    CharMotionShiftSet(playerP->charNo, playerP->omObj->mtnId[MGPLAYER_MOT_IDLE], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
                    playerP->motNo = MGPLAYER_MOT_IDLE;
                }
                Hu3DMotionSpeedSet(player->unk014, 1.0f);
            }
        }
    } else {
        if (fabsf(playerP->actor->velY) > 2000.0f) {
            MgPlayerModeSet(playerP, MGPLAYER_MODE_FALL);
        }
    }
}
