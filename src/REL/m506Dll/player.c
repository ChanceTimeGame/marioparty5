#include "REL/m506Dll.h"

#include "game/charman.h"
#include "game/frand.h"
#include "game/pad.h"
#include "datanum/charmot.h"

#include <string.h>

/*
 * Written here from the reference assembly; upstream declares this unit
 * NonMatching and ships no source for it. Function names come from upstream's
 * symbols.txt. See NOTES.md for how it was checked.
 */

#define M506_MODE_NORMAL_JUMP 0
#define M506_MODE_UP_JUMP 1
#define M506_MODE_SIDE_JUMP 2
#define M506_MODE_FALL 3
#define M506_MODE_IDLE 4

#define M506_MOT_IDLE 0
#define M506_MOT_JUMP_LAND 2
#define M506_MOT_FALL_LOOP 3
#define M506_MOT_SHIFT_IDLE 7
#define M506_MOT_SHIFT_FALL 8
#define M506_MOT_SHIFT_JUMP 9
#define M506_MOT_SHIFT_BOUNCE 10

typedef int (*M506_PLAYER_MODE_FUNC)(OMOBJ *obj);

static s16 PlayerModeNoTbl[M506_PLAYER_MAX] = { 0 };

static unsigned int PlayerMotionTbl[13][7] = {
    { DATANUM(DATA_mariomot, 0x00), DATANUM(DATA_mariomot, 0x03), DATANUM(DATA_mariomot, 0x04), DATANUM(DATA_mariomot, 0x2B), DATANUM(DATA_mariomot, 0x06), DATANUM(DATA_mariomot, 0x07), DATANUM(DATA_mariomot, 0x0D) },
    { DATANUM(DATA_luigimot, 0x00), DATANUM(DATA_luigimot, 0x03), DATANUM(DATA_luigimot, 0x04), DATANUM(DATA_luigimot, 0x2B), DATANUM(DATA_luigimot, 0x06), DATANUM(DATA_luigimot, 0x07), DATANUM(DATA_luigimot, 0x0D) },
    { DATANUM(DATA_peachmot, 0x00), DATANUM(DATA_peachmot, 0x03), DATANUM(DATA_peachmot, 0x04), DATANUM(DATA_peachmot, 0x2B), DATANUM(DATA_peachmot, 0x06), DATANUM(DATA_peachmot, 0x31), DATANUM(DATA_peachmot, 0x0D) },
    { DATANUM(DATA_yoshimot, 0x00), DATANUM(DATA_yoshimot, 0x03), DATANUM(DATA_yoshimot, 0x04), DATANUM(DATA_yoshimot, 0x2B), DATANUM(DATA_yoshimot, 0x06), DATANUM(DATA_yoshimot, 0x07), DATANUM(DATA_yoshimot, 0x0D) },
    { DATANUM(DATA_wariomot, 0x00), DATANUM(DATA_wariomot, 0x03), DATANUM(DATA_wariomot, 0x04), DATANUM(DATA_wariomot, 0x2B), DATANUM(DATA_wariomot, 0x06), DATANUM(DATA_wariomot, 0x07), DATANUM(DATA_wariomot, 0x0D) },
    { DATANUM(DATA_daisymot, 0x00), DATANUM(DATA_daisymot, 0x03), DATANUM(DATA_daisymot, 0x04), DATANUM(DATA_daisymot, 0x2B), DATANUM(DATA_daisymot, 0x06), DATANUM(DATA_daisymot, 0x07), DATANUM(DATA_daisymot, 0x0D) },
    { DATANUM(DATA_waluigimot, 0x00), DATANUM(DATA_waluigimot, 0x03), DATANUM(DATA_waluigimot, 0x04), DATANUM(DATA_waluigimot, 0x2B), DATANUM(DATA_waluigimot, 0x06), DATANUM(DATA_waluigimot, 0x07), DATANUM(DATA_waluigimot, 0x0D) },
    { DATANUM(DATA_kinopiomot, 0x00), DATANUM(DATA_kinopiomot, 0x03), DATANUM(DATA_kinopiomot, 0x04), DATANUM(DATA_kinopiomot, 0x2B), DATANUM(DATA_kinopiomot, 0x06), DATANUM(DATA_kinopiomot, 0x07), DATANUM(DATA_kinopiomot, 0x0D) },
    { DATANUM(DATA_teresamot, 0x00), DATANUM(DATA_teresamot, 0x03), DATANUM(DATA_teresamot, 0x04), DATANUM(DATA_teresamot, 0x2B), DATANUM(DATA_teresamot, 0x06), DATANUM(DATA_teresamot, 0x07), DATANUM(DATA_teresamot, 0x0D) },
    { DATANUM(DATA_minikoopamot, 0x00), DATANUM(DATA_minikoopamot, 0x03), DATANUM(DATA_minikoopamot, 0x04), DATANUM(DATA_minikoopamot, 0x2B), DATANUM(DATA_minikoopamot, 0x06), DATANUM(DATA_minikoopamot, 0x07), DATANUM(DATA_minikoopamot, 0x0D) },
    { DATANUM(DATA_minikoopamot, 0x00), DATANUM(DATA_minikoopamot, 0x03), DATANUM(DATA_minikoopamot, 0x04), DATANUM(DATA_minikoopamot, 0x2B), DATANUM(DATA_minikoopamot, 0x06), DATANUM(DATA_minikoopamot, 0x07), DATANUM(DATA_minikoopamot, 0x0D) },
    { DATANUM(DATA_minikoopamot, 0x00), DATANUM(DATA_minikoopamot, 0x03), DATANUM(DATA_minikoopamot, 0x04), DATANUM(DATA_minikoopamot, 0x2B), DATANUM(DATA_minikoopamot, 0x06), DATANUM(DATA_minikoopamot, 0x07), DATANUM(DATA_minikoopamot, 0x0D) },
    { DATANUM(DATA_minikoopamot, 0x00), DATANUM(DATA_minikoopamot, 0x03), DATANUM(DATA_minikoopamot, 0x04), DATANUM(DATA_minikoopamot, 0x2B), DATANUM(DATA_minikoopamot, 0x06), DATANUM(DATA_minikoopamot, 0x07), DATANUM(DATA_minikoopamot, 0x0D) }
};

// Per CPU difficulty: next-input delay min/max, percent chance to jump the
// correct way outright, and the min/max of the budget for deliberate misses.
static s16 ComMaxDelayTbl[4][5] = {
    { 40, 52, 25, 8, 40 },
    { 15, 28, 75, 7, 15 },
    { 6, 15, 85, 4, 7 },
    { 4, 9, 90, 2, 6 }
};

static int FallStartFXTbl[M506_PLAYER_MAX] = { 0x66F, 0x670, 0x671, 0x672 };
static int FallEndFXTbl[M506_PLAYER_MAX] = { 0x673, 0x674, 0x675, 0x676 };
static int CharFallFXTbl[13] = { 0x1F9, 0x1E5, 0x25D, 0x2AD, 0x285, 0x1BD, 0x299, 0x1D1, 0x271, 0x235, 0x249, 0x221, 0x20D };
static int PlayerPanTbl[M506_PLAYER_MAX] = { 40, 56, 72, 88 };

int M506PlayerModeNormalJump(OMOBJ *obj);
int M506PlayerModeUpJump(OMOBJ *obj);
int M506PlayerModeSideJump(OMOBJ *obj);
int M506PlayerModeFall(OMOBJ *obj);

static M506_PLAYER_MODE_FUNC PlayerModeTbl[4] = {
    M506PlayerModeNormalJump,
    M506PlayerModeUpJump,
    M506PlayerModeSideJump,
    M506PlayerModeFall
};

static float MotSpeedTbl[10] = { 1, 0.75f, 1, 1, 1, 1, 1, 1, 1, 1 };

// Indexed by motion number minus M506_MOT_SHIFT_IDLE: motion slot, shift start, shift length.
static float MotShiftTbl[4][3] = {
    { 0, 0, 3 },
    { 3, 0, 5 },
    { 1, 0, 8 },
    { 2, 0, 12 }
};

static float JumpUpSpeedTbl[15] = { 38, 36, 34, 32, 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10 };
static float JumpDownSpeedTbl[8] = { 0, -2, -4, -6, -9, -11, -13, -15 };
static float BounceUpSpeedTbl[7] = { 20, 18, 16, 14, 12, 10, 8 };
static float BounceDownSpeedTbl[8] = { 0, -8, -10, -12, -14, -16, -18, -20 };

static int CharFallSeNo[M506_PLAYER_MAX];
static int FallEndSeNo[M506_PLAYER_MAX];
static int FallStartSeNo[M506_PLAYER_MAX];

void M506PlayerUpdate(OMOBJ *obj);
int M506PlayerInputRead(OMOBJ *obj);
s16 M506ComInputCheck(OMOBJ *obj);

void M506PlayerCreate(OMOBJ *obj)
{
    M506_PLAYER_WORK *player = obj->data;
    s16 i;

    memset(player, 0, sizeof(M506_PLAYER_WORK));
    player->no = obj->work[0];
    player->charNo = GwPlayerConf[player->no].charNo;
    player->padNo = GwPlayerConf[player->no].padNo;
    player->playerType = GwPlayerConf[player->no].type;
    player->comDif = GwPlayerConf[player->no].dif;
    player->unkC = player->unk10 = 0;
    player->newHeight = player->height = 0;
    player->motId = M506_MOT_IDLE;
    player->curDir = -1;
    player->upJumpF = FALSE;
    player->comMoveChance = 0;
    player->comMoveChanceMax = ComMaxDelayTbl[player->comDif][3]
        + frandmod(ComMaxDelayTbl[player->comDif][4] - ComMaxDelayTbl[player->comDif][3]);
    player->comMoveChanceMax = (player->comMoveChanceMax * 45) + 15;
    player->pos.x = -64.5f;
    player->pos.y = 0;
    player->pos.z = 179;
    PlayerModeNoTbl[player->no] = M506_MODE_IDLE;
    if(player->no == 0) {
        obj->mdlId[0] = CharModelCreate(player->charNo, 4);
    } else {
        obj->mdlId[0] = CharModelCreate(player->charNo, 8);
    }
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    Hu3DModelShadowSet(obj->mdlId[0]);
    CharModelStepFxSet(player->charNo, 1);
    for(i=0; i<7; i++) {
        obj->mtnId[i] = CharMotionCreate(player->charNo, PlayerMotionTbl[player->charNo][i]);
    }
    CharMotionUpdateSet(player->charNo, CHARMOT_HSF_c000m1_304, FALSE);
    CharMotionVoiceOnSet(player->charNo, 0x2B, FALSE);
    CharMotionSet(player->charNo, obj->mtnId[0]);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(obj->mdlId[0], 5);
    Hu3DModelCameraSet(obj->mdlId[0], M506CameraBit[player->no]);
    CharEffectLayerSet(6);
    CharMotionDataClose(player->charNo);
    CharModelVoicePanSet(player->charNo, PlayerPanTbl[player->no]);
    obj->objFunc = M506PlayerUpdate;
}

void M506PlayerUpdate(OMOBJ *obj)
{
    M506_PLAYER_WORK *player = obj->data;
    u32 *mode = &M506MainObj->work[3];

    switch(*mode) {
        case 0:
        case 1:
            break;

        case 2:
            if(PlayerModeNoTbl[player->no] == M506_MODE_IDLE) {
                M506PlayerInputRead(obj);
                if(PlayerModeNoTbl[player->no] != M506_MODE_IDLE) {
                    PlayerModeTbl[PlayerModeNoTbl[player->no]](obj);
                }
            } else {
                PlayerModeTbl[PlayerModeNoTbl[player->no]](obj);
            }
            break;

        case 3:
        case 4:
            if(PlayerModeNoTbl[player->no] != M506_MODE_IDLE) {
                PlayerModeTbl[PlayerModeNoTbl[player->no]](obj);
            }
            break;
    }
}

void M506PlayerMotionSet(OMOBJ *obj, u32 motNo)
{
    M506_PLAYER_WORK *player = obj->data;
    u32 shiftAttr = HU3D_ATTR_NONE;

    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(obj->mdlId[0], MotSpeedTbl[motNo]);
    player->motId = motNo;
    switch(motNo) {
        case 0:
        case 3:
            Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
        case 2:
        case 4:
        case 5:
            Hu3DMotionSet(obj->mdlId[0], obj->mtnId[motNo]);
            break;

        case 7:
            shiftAttr = HU3D_ATTR_NONE;
        case 8:
            M506ObjShadowMapReset(player->no, player->newHeight, player->height);
        case 9:
        case 10:
            Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[(int)MotShiftTbl[motNo-7][0]],
                MotShiftTbl[motNo-7][1], MotShiftTbl[motNo-7][2], shiftAttr);
            break;
    }
}

BOOL M506PlayerMotionEndCheck(OMOBJ *obj)
{
    M506_PLAYER_WORK *player = obj->data;
    BOOL endF = FALSE;

    if(player->motId < 7) {
        player->motTime = Hu3DMotionTimeGet(obj->mdlId[0]);
    } else {
        player->motTime = Hu3DMotionShiftTimeGet(obj->mdlId[0]);
    }
    if(player->motTime >= player->motMaxTime) {
        endF = TRUE;
    }
    return endF;
}

int M506PlayerInputRead(OMOBJ *obj)
{
    M506_PLAYER_WORK *player = obj->data;
    M506_WORK *m506Work = M506MainObj->data;
    int result = 0;
    s16 inputF = FALSE;
    M506_WORK *work = m506Work;
    s16 i;

    if(player->newHeight < M506_JUMP_MAX) {
        if(player->playerType == GW_TYPE_MAN) {
            if(HuPadBtnDown[player->padNo] & PAD_BUTTON_A) {
                player->curDir = -1;
                inputF = TRUE;
            }
            if(HuPadStkX[player->padNo] > 32 && (HuPadBtnDown[player->padNo] & PAD_BUTTON_A)) {
                player->curDir = 1;
                inputF = TRUE;
            }
            if(HuPadStkX[player->padNo] < -32 && (HuPadBtnDown[player->padNo] & PAD_BUTTON_A)) {
                player->curDir = 0;
                inputF = TRUE;
            }
        } else if(player->playerType == GW_TYPE_COM) {
            inputF = M506ComInputCheck(obj);
        }
    }
    if(inputF) {
        player->jumpTicks = 0;
        player->jumpF = FALSE;
        player->modeTimer = 0;
        if(player->newHeight == 0) {
            player->nextJumpF = TRUE;
        } else {
            player->nextJumpF = FALSE;
        }
        if(player->curDir != -1 && player->curDir != player->prevDir) {
            if(player->curDir == work->mameSide[player->no][player->newHeight]) {
                PlayerModeNoTbl[player->no] = M506_MODE_SIDE_JUMP;
                if(++player->newHeight > player->height) {
                    player->height++;
                    player->jumpF = TRUE;
                }
            } else {
                PlayerModeNoTbl[player->no] = M506_MODE_FALL;
                player->upJumpF = TRUE;
                if(player->newHeight != 0) {
                    player->fallLevel++;
                    i = player->newHeight;
                    do {
                        if(work->mameSide[player->no][i-1] == player->curDir) {
                            break;
                        }
                        player->fallLevel++;
                    } while(--i != 0);
                    player->prevHeight = player->newHeight;
                    player->newHeight = i;
                } else {
                    player->fallLevel = 1;
                }
            }
            player->prevDir = player->curDir;
        } else {
            if(work->mameSide[player->no][player->newHeight] == player->prevDir) {
                PlayerModeNoTbl[player->no] = M506_MODE_NORMAL_JUMP;
                if(++player->newHeight > player->height) {
                    player->height++;
                    player->jumpF = TRUE;
                }
            } else {
                PlayerModeNoTbl[player->no] = M506_MODE_UP_JUMP;
                player->upJumpF = TRUE;
            }
        }
    }
    return result;
}

static inline void M506PlayerLand(M506_PLAYER_WORK *player, s16 off, s16 on)
{
    CharModelLandDustCreate(player->charNo, &player->pos);
    omVibrate(player->no, 12, off, on);
}

int M506PlayerModeNormalJump(OMOBJ *obj)
{
    M506_PLAYER_WORK *player = obj->data;
    int result = 0;

    player->jumpTicks++;
    player->modeTimer++;
    M506MameUpdate(player);
    M506YCamera->camera[player->no].pos.y += 10;
    switch(player->mode) {
        case 0:
            M506PlayerMotionSet(obj, M506_MOT_SHIFT_JUMP);
            player->mode++;
            player->jumpTimer = 0;
            M506ObjShadowMapSet(player->no, player->newHeight);

        case 1:
            if(player->newHeight != 1) {
                player->pos.y += JumpUpSpeedTbl[player->jumpTimer];
            } else {
                player->pos.y += 4.8f+JumpUpSpeedTbl[player->jumpTimer];
            }
            player->jumpTimer++;
            omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            if(player->modeTimer > 14) {
                M506PlayerMotionSet(obj, M506_MOT_JUMP_LAND);
                player->mode++;
                player->jumpTimer = 0;
            }
            break;

        case 2:
            M506MameModeEnter(player);
            if(player->jumpTimer < 8) {
                player->pos.y += JumpDownSpeedTbl[player->jumpTimer];
                omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
                if(player->jumpTimer >= 7) {
                    M506PlayerLand(player, 6, 6);
                }
            }
            player->jumpTimer++;
            if(player->modeTimer > 26) {
                M506PlayerMotionSet(obj, M506_MOT_SHIFT_IDLE);
                player->mode++;
            }
            break;

        case 3:
            M506MameModeEnter(player);
            if(player->modeTimer > 29) {
                M506PlayerMotionSet(obj, M506_MOT_IDLE);
                player->mode = 0;
                player->curDir = -1;
                PlayerModeNoTbl[player->no] = M506_MODE_IDLE;
                result = 1;
            }
            break;
    }
    M506MameModeJump(player);
    return result;
}

int M506PlayerModeUpJump(OMOBJ *obj)
{
    M506_PLAYER_WORK *player = obj->data;
    int result = 0;

    player->modeTimer++;
    switch(player->mode) {
        case 0:
            M506PlayerMotionSet(obj, M506_MOT_SHIFT_JUMP);
            player->jumpTimer = 0;
            player->mode++;

        case 1:
            if(!player->nextJumpF) {
                player->pos.y += JumpUpSpeedTbl[player->jumpTimer];
            } else {
                player->pos.y += 4.8f+JumpUpSpeedTbl[player->jumpTimer];
            }
            player->jumpTimer++;
            omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            if(player->modeTimer > 14) {
                player->jumpTimer = 0;
                player->mode++;
            }
            break;

        case 2:
            if(player->jumpTimer < 8) {
                player->pos.y += JumpDownSpeedTbl[player->jumpTimer];
            } else if(!player->nextJumpF) {
                player->pos.y -= 20;
            } else {
                player->pos.y -= 24.8f;
            }
            omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            player->jumpTimer++;
            if(player->modeTimer > 29) {
                M506PlayerMotionSet(obj, M506_MOT_JUMP_LAND);
                player->jumpTimer = 0;
                player->mode++;
            }
            break;

        case 3:
            M506MameModeEnter(player);
            if(player->jumpTimer < 8) {
                if(!player->nextJumpF) {
                    player->pos.y -= 20;
                } else {
                    player->pos.y -= 24.8f;
                }
                omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
                if(player->jumpTimer >= 7) {
                    M506PlayerLand(player, 6, 6);
                }
            }
            player->jumpTimer++;
            if(player->modeTimer > 41) {
                M506PlayerMotionSet(obj, M506_MOT_SHIFT_IDLE);
                player->mode++;
            }
            break;

        case 4:
            M506MameModeEnter(player);
            if(player->modeTimer > 44) {
                M506PlayerMotionSet(obj, M506_MOT_IDLE);
                player->mode = 0;
                player->curDir = -1;
                PlayerModeNoTbl[player->no] = M506_MODE_IDLE;
                result = 1;
            }
            break;
    }
    return result;
}

int M506PlayerModeSideJump(OMOBJ *obj)
{
    M506_PLAYER_WORK *player = obj->data;
    int result = 0;

    M506YCamera->camera[player->no].pos.y += 10;
    player->jumpTicks++;
    player->modeTimer++;
    M506MameUpdate(player);
    switch(player->mode) {
        case 0:
            M506PlayerMotionSet(obj, M506_MOT_SHIFT_JUMP);
            player->jumpTimer = 0;
            player->mode++;
            M506ObjShadowMapSet(player->no, player->newHeight);

        case 1:
            if(player->curDir == 0) {
                player->pos.x -= 5.6f;
            } else {
                player->pos.x += 5.6f;
            }
            if(player->newHeight != 1) {
                player->pos.y += JumpUpSpeedTbl[player->jumpTimer];
            } else {
                player->pos.y += 4.8f+JumpUpSpeedTbl[player->jumpTimer];
            }
            player->jumpTimer++;
            omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            if(player->modeTimer > 14) {
                M506PlayerMotionSet(obj, M506_MOT_JUMP_LAND);
                player->jumpTimer = 0;
                player->mode++;
            }
            break;

        case 2:
            M506MameModeEnter(player);
            if(player->jumpTimer < 8) {
                if(player->curDir == 0) {
                    player->pos.x -= 5.6f;
                } else {
                    player->pos.x += 5.6f;
                }
                player->pos.y += JumpDownSpeedTbl[player->jumpTimer];
                omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
                if(player->jumpTimer >= 7) {
                    M506PlayerLand(player, 6, 6);
                }
            }
            player->jumpTimer++;
            if(player->modeTimer > 26) {
                M506PlayerMotionSet(obj, M506_MOT_SHIFT_IDLE);
                player->jumpTimer = 0;
                player->mode++;
            }
            break;

        case 3:
            M506MameModeEnter(player);
            if(player->modeTimer > 29) {
                M506PlayerMotionSet(obj, M506_MOT_IDLE);
                player->mode = 0;
                player->curDir = -1;
                PlayerModeNoTbl[player->no] = M506_MODE_IDLE;
                result = 1;
            }
            break;
    }
    return result;
}

static inline void M506PlayerFallStep(M506_PLAYER_WORK *player)
{
    if(player->newHeight != 0) {
        if(player->jumpTimer < 8) {
            player->pos.y += JumpDownSpeedTbl[player->jumpTimer];
        } else {
            player->pos.y -= 20;
        }
    } else if(player->jumpTimer < 8) {
        player->pos.y += JumpDownSpeedTbl[player->jumpTimer];
    } else if((player->fallLevel*15)-player->fallTime < 15) {
        player->pos.y -= 24.8f;
    } else {
        player->pos.y -= 20;
    }
    if(player->jumpTimer < 8) {
        if(player->curDir == 0) {
            player->pos.x -= 5.6f;
        } else {
            player->pos.x += 5.6f;
        }
    }
}

int M506PlayerModeFall(OMOBJ *obj)
{
    M506_PLAYER_WORK *player = obj->data;
    int result = 0;

    player->modeTimer++;
    switch(player->mode) {
        case 0:
            M506PlayerMotionSet(obj, M506_MOT_SHIFT_JUMP);
            player->jumpTimer = 0;
            player->mode++;

        case 1:
            M506MameModeMiss(player);
            if(player->curDir == 0) {
                player->pos.x -= 5.6f;
            } else {
                player->pos.x += 5.6f;
            }
            if(!player->nextJumpF) {
                player->pos.y += JumpUpSpeedTbl[player->jumpTimer];
            } else {
                player->pos.y += 4.8f+JumpUpSpeedTbl[player->jumpTimer];
            }
            player->jumpTimer++;
            omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            if(player->modeTimer > 14) {
                if(!player->nextJumpF) {
                    M506PlayerMotionSet(obj, M506_MOT_SHIFT_FALL);
                    FallStartSeNo[player->no] = HuAudFXPlay(FallStartFXTbl[player->no]);
                    HuAudFXPanning(FallStartSeNo[player->no], PlayerPanTbl[player->no]);
                    CharFallSeNo[player->no] = HuAudFXPlay(CharFallFXTbl[player->charNo]);
                    HuAudFXPanning(CharFallSeNo[player->no], PlayerPanTbl[player->no]);
                    player->mode++;
                } else {
                    player->mode = 8;
                }
                player->fallTime = 0;
                player->jumpTimer = 0;
            }
            break;

        case 2:
            M506MameModeMiss(player);
            player->fallTime++;
            M506PlayerFallStep(player);
            omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            if(player->jumpTimer > 7 && player->fallTime <= ((player->fallLevel-1)*15)+8) {
                M506YCamera->camera[player->no].pos.y -= 20;
            }
            player->jumpTimer++;
            if(player->modeTimer > 19) {
                M506PlayerMotionSet(obj, M506_MOT_FALL_LOOP);
                player->mode++;
            }
            break;

        case 3:
            if(player->modeTimer < 31) {
                M506MameModeMiss(player);
            }
            player->fallTime++;
            M506PlayerFallStep(player);
            omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            if(player->jumpTimer > 7 && player->fallTime <= ((player->fallLevel-1)*15)+8) {
                M506YCamera->camera[player->no].pos.y -= 20;
            }
            player->jumpTimer++;
            if(player->fallTime >= player->fallLevel*15) {
                player->jumpTimer = 0;
                player->prevFallTime = player->fallTime;
                player->mode++;
            }
            break;

        case 4:
            if(player->modeTimer < 31) {
                M506MameModeMiss(player);
            }
            if(player->jumpTimer < 8) {
                M506MameModeEnter(player);
                if(!player->nextJumpF) {
                    player->pos.y -= 20;
                } else {
                    player->pos.y -= 24.8f;
                }
                omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
                if(player->jumpTimer >= 7) {
                    M506PlayerLand(player, 4, 2);
                }
            }
            player->jumpTimer++;
            player->fallTime++;
            if(player->fallTime <= ((player->fallLevel-1)*15)+8) {
                M506YCamera->camera[player->no].pos.y -= 20;
            }
            if(player->jumpTimer >= 9) {
                player->fallTime = 0;
                player->jumpTimer = 0;
                player->mode++;
                FallEndSeNo[player->no] = HuAudFXPlay(FallEndFXTbl[player->no]);
                HuAudFXPanning(FallEndSeNo[player->no], PlayerPanTbl[player->no]);
            }
            break;

        case 5:
            if(player->jumpTimer < 7) {
                M506MameModeEnter(player);
                player->pos.y += BounceUpSpeedTbl[player->jumpTimer];
                omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            }
            player->jumpTimer++;
            if(player->jumpTimer >= 7) {
                M506PlayerMotionSet(obj, M506_MOT_SHIFT_BOUNCE);
                player->jumpTimer = 0;
                player->mode++;
            }
            break;

        case 6:
            if(player->jumpTimer < 8) {
                player->pos.y += BounceDownSpeedTbl[player->jumpTimer];
                omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            }
            player->jumpTimer++;
            if(player->jumpTimer >= 12) {
                M506PlayerMotionSet(obj, M506_MOT_JUMP_LAND);
                Hu3DMotionTimeSet(obj->mdlId[0], Hu3DMotionMotionMaxTimeGet(obj->mdlId[0]));
                M506PlayerMotionSet(obj, M506_MOT_SHIFT_IDLE);
                player->jumpTimer = 1;
                player->mode++;
            }
            break;

        case 7:
            player->jumpTimer++;
            if(player->jumpTimer > 3) {
                M506PlayerMotionSet(obj, M506_MOT_IDLE);
                player->mode = 0;
                player->fallLevel = 0;
                player->curDir = -1;
                PlayerModeNoTbl[player->no] = M506_MODE_IDLE;
                result = 1;
            }
            break;

        case 8:
            M506MameModeMiss(player);
            if(player->jumpTimer < 8) {
                if(player->curDir == 0) {
                    player->pos.x -= 5.6f;
                } else {
                    player->pos.x += 5.6f;
                }
                player->pos.y += JumpDownSpeedTbl[player->jumpTimer];
            } else {
                player->pos.y -= 24.8f;
            }
            omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            player->jumpTimer++;
            if(player->modeTimer > 29) {
                M506PlayerMotionSet(obj, M506_MOT_JUMP_LAND);
                player->jumpTimer = 0;
                player->mode++;
            }
            break;

        case 9:
            M506MameModeEnter(player);
            if(player->jumpTimer < 8) {
                player->pos.y -= 24.8f;
                omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
                if(player->jumpTimer >= 7) {
                    M506PlayerLand(player, 6, 6);
                }
            }
            player->jumpTimer++;
            if(player->modeTimer > 41) {
                M506PlayerMotionSet(obj, M506_MOT_SHIFT_IDLE);
                player->mode++;
            }
            break;

        case 10:
            M506MameModeEnter(player);
            if(player->modeTimer > 44) {
                M506PlayerMotionSet(obj, M506_MOT_IDLE);
                player->mode = 0;
                player->fallLevel = 0;
                player->curDir = -1;
                PlayerModeNoTbl[player->no] = M506_MODE_IDLE;
                result = 1;
            }
            break;
    }
    return result;
}

s16 M506ComInputDelayGet(OMOBJ *obj)
{
    M506_PLAYER_WORK *player = obj->data;
    M506_WORK *m506Work = M506MainObj->data;
    s16 delay = 0;
    s16 unused = 0;
    M506_WORK *work = m506Work;
    s16 side;
    s16 i;

    if(player->prevDir == work->mameSide[player->no][player->newHeight]) {
        if(player->prevDir == 1) {
            side = 0;
        } else {
            side = 1;
        }
        if(player->newHeight != 0) {
            delay++;
            i = player->newHeight;
            while(1) {
                if(work->mameSide[player->no][i-1] == side) {
                    break;
                }
                delay++;
                if(--i == 0) {
                    break;
                }
            }
        } else {
            delay = 1;
        }
    } else {
        delay = 1;
    }
    if(delay >= 2) {
        delay = (delay*45)+15;
    } else {
        delay = delay*45;
    }
    return delay;
}

s16 M506ComInputCheck(OMOBJ *obj)
{
    M506_PLAYER_WORK *player = obj->data;
    M506_WORK *m506Work = M506MainObj->data;
    u32 chance = 0;
    s16 inputF = FALSE;
    s16 jumpType = -1;
    M506_WORK *work = m506Work;
    s16 delay;

    switch(player->comMode) {
        case 0:
            player->comDelayMax = ComMaxDelayTbl[player->comDif][0]
                + frandmod(ComMaxDelayTbl[player->comDif][1] - ComMaxDelayTbl[player->comDif][0]);
            if(player->nextJumpF == TRUE) {
                player->comDelayMax /= 2;
            }
            if(!player->jumpF) {
                player->comDelayMax /= 2;
            } else if(player->comRecoverF) {
                player->comDelayMax /= 2;
            }
            player->comMode++;

        case 1:
            if(player->comDelayMax <= ++player->comDelay) {
                chance = frandmod(100);
                if(chance <= ComMaxDelayTbl[player->comDif][2]) {
                    jumpType = 1;
                } else {
                    delay = M506ComInputDelayGet(obj);
                    if(delay+player->comMoveChance > player->comMoveChanceMax) {
                        jumpType = 1;
                    } else {
                        jumpType = 0;
                        player->comMoveChance += delay;
                    }
                }
                if(player->nextJumpF == TRUE) {
                    jumpType = 1;
                }
                if(!player->jumpF) {
                    jumpType = 1;
                } else if(player->comRecoverF) {
                    player->comRecoverF = FALSE;
                    jumpType = 1;
                }
                player->comMode = 0;
                player->comDelayMax = 0;
                player->comDelay = 0;
            }
            break;
    }
    if(jumpType == 1) {
        player->curDir = work->mameSide[player->no][player->newHeight];
        inputF = TRUE;
    } else if(jumpType == 0) {
        if(work->mameSide[player->no][player->newHeight] == 0) {
            player->curDir = 1;
        } else if(work->mameSide[player->no][player->newHeight] == 1) {
            player->curDir = 0;
        }
        player->comRecoverF = TRUE;
        inputF = TRUE;
    }
    return inputF;
}
