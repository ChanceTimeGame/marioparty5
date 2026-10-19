/*
 * sd00dll com.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sd00dll/asm/REL/sd00dll/com.s.
 */

#include "REL/sd00dll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"
#include "humath.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x6A8 lbl_1_rodata_6A8 (0x14): 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6BC lbl_1_rodata_6BC (0xC): 0x00000005 0x00000003 0x00000001 -- an aggregate initialiser, write it as a local */
/* 0x6C8 lbl_1_rodata_6C8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6D4 lbl_1_rodata_6D4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6E0 lbl_1_rodata_6E0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6EC lbl_1_rodata_6EC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6F8 lbl_1_rodata_6F8 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x704 lbl_1_rodata_704 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x710 lbl_1_rodata_710 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x71C lbl_1_rodata_71C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x728 lbl_1_rodata_728 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x734 lbl_1_rodata_734 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x740 lbl_1_rodata_740 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x74C lbl_1_rodata_74C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x758 lbl_1_rodata_758 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x764 lbl_1_rodata_764 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x770 lbl_1_rodata_770 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x77C lbl_1_rodata_77C (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x788 lbl_1_rodata_788 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_794 = 0.0f; /* 0x794 */
static const float lbl_1_rodata_798 = -1.0f; /* 0x798 */
static const float lbl_1_rodata_79C = -10000.0f; /* 0x79C */
static const float lbl_1_rodata_7A0 = 4.0f; /* 0x7A0 */
static const float lbl_1_rodata_7A4 = 300.0f; /* 0x7A4 */
static const float lbl_1_rodata_7A8 = -200.0f; /* 0x7A8 */
static const float lbl_1_rodata_7AC = 2.0f; /* 0x7AC */
static const float lbl_1_rodata_7B0 = -1.5f; /* 0x7B0 */
static const float lbl_1_rodata_7B4 = 600.0f; /* 0x7B4 */
static const float lbl_1_rodata_7B8 = 150.0f; /* 0x7B8 */
static const float lbl_1_rodata_7BC = 200.0f; /* 0x7BC */
static const float lbl_1_rodata_7C0 = 100.0f; /* 0x7C0 */
static const float lbl_1_rodata_7C4 = 400.0f; /* 0x7C4 */
static const float lbl_1_rodata_7C8 = 0.1f; /* 0x7C8 */
static const float lbl_1_rodata_7CC = 5.0f; /* 0x7CC */
static const double lbl_1_rodata_7D0 = 180.0; /* 0x7D0 */
static const double lbl_1_rodata_7D8 = 3.141592653589793; /* 0x7D8 */
static const float lbl_1_rodata_7E0 = 0.017453292f; /* 0x7E0 */
static const float lbl_1_rodata_7E4 = 180.0f; /* 0x7E4 */
static const float lbl_1_rodata_7E8 = 360.0f; /* 0x7E8 */
static const float lbl_1_rodata_7EC = 1000.0f; /* 0x7EC */
static const float lbl_1_rodata_7F0 = 10.0f; /* 0x7F0 */
static const float lbl_1_rodata_7F4 = 45.0f; /* 0x7F4 */
static const float lbl_1_rodata_7F8 = 15.0f; /* 0x7F8 */
static const float lbl_1_rodata_7FC = 0.5f; /* 0x7FC */
static const float lbl_1_rodata_800 = 60.0f; /* 0x800 */
static const float lbl_1_rodata_804 = 30.0f; /* 0x804 */
static const float lbl_1_rodata_808 = 0.25f; /* 0x808 */
static const float lbl_1_rodata_80C = 0.9f; /* 0x80C */
static const float lbl_1_rodata_810 = 8.0f; /* 0x810 */
static const float lbl_1_rodata_814 = 10000.0f; /* 0x814 */
static const float lbl_1_rodata_818 = 1500.0f; /* 0x818 */
static const float lbl_1_rodata_81C = -180.0f; /* 0x81C */
static const double lbl_1_rodata_820 = -56.0; /* 0x820 */
static const double lbl_1_rodata_828 = 56.0; /* 0x828 */
/* 0x830 lbl_1_rodata_830 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0x838 lbl_1_rodata_838 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x844 lbl_1_rodata_844 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_850 = 12.0f; /* 0x850 */
static const double lbl_1_rodata_858 = 1.3089969389957472; /* 0x858 */
/* 0x860 lbl_1_rodata_860 (0xC): 0xC61C4000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x86C gap_03_0000086C_rodata: 0x00000000 */

static float ComObjDistGet(SDMACHINE *machine, HuVecF dir);
static s32 ComNextModeFarGet(SDMACHINE *machine);
static s32 ComNextModeNearGet(SDMACHINE *machine);
static HuVecF ComStageObjPosGet(SDMACHINE *machine);
static void ComRandomizeMachine(SDMACHINE *machine, s32 a1, s32 a2, s32 a3);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x1018 */ static s32 comDataTbl[12][3] = { 0x1, 0x2, 0x2, 0x1, 0x2, 0x2, 0x2, 0x1, 0x2, 0x2, 0x1, 0x1, 0x2, 0x1, 0x1, 0x2, 0x3, 0x3, 0x3, 0x2, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x5, 0x5 };
/* 2285 insns */
void SdComMain(SDMACHINE *machine)
{
    Mtx rotMtx;
    s32 hit[5] = { 0, 0, 0, 0, 0 };
    s32 levelTbl[3] = { 5, 3, 1 };
    HuVecF front;
    HuVecF back;
    HuVecF aimDir;
    HuVecF side;
    HuVecF sideInv;
    HuVecF diff;
    HuVecF lead;
    HuVecF dir;
    HuVecF ofs;
    HuVecF goal;
    HuVecF aimVel;
    HuVecF aimPos;
    HuVecF flagPos;
    HuVecF flagDir;
    HuVecF flagTarget;
    SDCOMWORK *com;
    SDMACHINE *enemy;
    s32 time;
    s32 check;
    float flagDist;
    float dist;
    float dot2;
    float dot1;
    SDBULLET *bullet;
    float stepLen;
    s32 i;
    float angle;
    float angle2;
    float tol;
    s32 fire; /* also the nearest-point index of the stage-0 search (one variable in retail) */
    float limit;

    com = &machine->com;
    enemy = machine->enemy;
    HuPadBtn[machine->unk348] = HuPadBtnDown[machine->unk348] = HuPadStkX[machine->unk348] = 0;
    if (com->unk38 != 0) {
        HuPadBtn[machine->unk348] |= PAD_BUTTON_A;
    }
    front = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
    front.y = 0.0f;
    VECNormalize(&front, &front);
    VECScale(&front, &back, -1.0f);
    side = (HuVecF){ machine->mtx[0][0], machine->mtx[1][0], machine->mtx[2][0] };
    side.y = 0.0f;
    VECNormalize(&side, &side);
    VECScale(&side, &sideInv, -1.0f);
    if (com->unk3C != -1) {
        com->unk40 = comDataTbl[com->unk3C][sys->gameType];
    } else {
        com->unk40 = levelTbl[sys->comLevel];
    }
    if (sys->gameType != 0) {
        if (sys->gameType == 1) {
            check = SdFlagCheck();
            flagPos = SdFlagPosGet();
            flagTarget = enemy->pos;
            flagDir = (HuVecF){ 0.0f, 0.0f, 0.0f };
        } else {
            check = SdRabbitCheck();
            flagPos = SdRabbitPosGet();
            flagTarget = flagPos;
            SdRabbitZAxisGet(&flagDir);
        }
        VECSubtract(&machine->pos, &flagPos, &diff);
        flagDist = VECMag(&diff);
        if (enemy->mode >= 2 || enemy->unk210 != 0) {
            if (check == 0) {
                com->unk38 = 2;
            } else {
                com->unk38 = ComNextModeNearGet(machine);
            }
        } else if (com->unk40 >= 3) {
            if (check != 0) {
                com->unk38 = ComNextModeNearGet(machine);
            } else {
                com->unk38 = 2;
            }
        } else if (check == 0) {
            com->unk38 = 1;
        } else {
            VECSubtract(&enemy->pos, &flagPos, &lead);
            if (flagDist < VECMag(&lead)) {
                com->unk38 = ComNextModeNearGet(machine);
            } else {
                com->unk38 = 1;
            }
        }
    } else {
        com->unk38 = ComNextModeFarGet(machine);
    }
    if (com->unk38 == 0) {
        return;
    }
    if (rand8() == 0) {
        if (GwPlayerConf[machine->playerNo].type != GW_TYPE_MAN && GwPlayerConf[enemy->playerNo].type != GW_TYPE_MAN) {
            ComRandomizeMachine(machine, rand8() % 5 - 2, rand8() % 5 - 2, rand8() % 5 - 2);
        } else {
            ComRandomizeMachine(machine, rand8() % 2 - 1, rand8() % 2, rand8() % 2 - 1);
        }
    }
    if (com->unk38 != 7) {
        com->unk50.x = -10000.0f;
    }
    if (com->unk38 != 4) {
        com->unk5C.x = -10000.0f;
    }
    switch (com->unk38) {
        case 0:
            break;
        case 1:
            goal = enemy->pos;
            aimPos = goal;
            aimVel = enemy->unk160;
            VECSubtract(&machine->pos, &goal, &diff);
            dist = VECMag(&diff);
            break;
        case 2:
            aimPos = enemy->pos;
            goal = (HuVecF){ enemy->mtx[0][0], enemy->mtx[1][0], enemy->mtx[2][0] };
            VECScale(&goal, &goal, 4.0f * enemy->unk358);
            VECAdd(&goal, &enemy->pos, &goal);
            aimVel = enemy->unk160;
            VECSubtract(&machine->pos, &goal, &diff);
            dist = VECMag(&diff);
            break;
        case 3:
            VECSubtract(&machine->pos, &enemy->pos, &dir);
            if (VECMag(&dir) == 0.0f) {
                dir = (HuVecF){ 1.0f, 1.0f, 1.0f };
            }
            VECNormalize(&dir, &dir);
            VECScale(&dir, &dir, 300.0f);
            VECAdd(&machine->pos, &dir, &dir);
            aimPos = dir;
            goal = aimPos;
            aimVel = (HuVecF){ 0.0f, 0.0f, 0.0f };
            VECSubtract(&machine->pos, &goal, &diff);
            dist = VECMag(&diff);
            break;
        case 4:
            if (-10000.0f == com->unk5C.x || com->unk34 % 90 == 0) {
                com->unk5C = SdStageRandomPosGet(-200.0f);
            }
            goal = com->unk5C;
            aimPos = goal;
            aimVel = (HuVecF){ 0.0f, 0.0f, 0.0f };
            VECSubtract(&machine->pos, &goal, &diff);
            dist = VECMag(&diff);
            break;
        case 5:
            aimPos = enemy->pos;
            goal = (HuVecF){ enemy->mtx[0][0], enemy->mtx[1][0], enemy->mtx[2][0] };
            VECScale(&goal, &goal, 2.0f * enemy->unk358);
            VECAdd(&goal, &enemy->pos, &goal);
            aimVel = enemy->unk160;
            VECSubtract(&machine->pos, &goal, &diff);
            dist = VECMag(&diff);
            break;
        case 6:
            aimPos = enemy->pos;
            dir = (HuVecF){ enemy->mtx[0][0], enemy->mtx[1][0], enemy->mtx[2][0] };
            VECScale(&dir, &dir, -1.5f);
            ofs = (HuVecF){ enemy->mtx[0][2], enemy->mtx[1][2], enemy->mtx[2][2] };
            VECScale(&ofs, &ofs, -1.0f);
            VECAdd(&dir, &ofs, &dir);
            if (VECMag(&dir) == 0.0f) {
                dir = (HuVecF){ 1.0f, 1.0f, 1.0f };
            }
            VECNormalize(&dir, &dir);
            VECScale(&dir, &goal, 2.0f * enemy->unk358);
            VECAdd(&goal, &enemy->pos, &goal);
            aimVel = enemy->unk160;
            VECSubtract(&machine->pos, &goal, &diff);
            dist = VECMag(&diff);
            break;
        case 8:
            goal = flagPos;
            aimVel = flagDir;
            dist = flagDist;
            aimPos = flagTarget;
            break;
        case 7:
            aimPos = enemy->pos;
            if (-10000.0f != com->unk50.x) {
                com->unk50 = ComStageObjPosGet(machine);
            }
            if (-10000.0f != com->unk50.x) {
                goal = com->unk50;
                aimVel = (HuVecF){ 0.0f, 0.0f, 0.0f };
            } else {
                com->unk50 = enemy->pos;
                goal = com->unk50;
                aimVel = enemy->unk160;
            }
            VECSubtract(&machine->pos, &goal, &diff);
            dist = VECMag(&diff);
            break;
    }
    if (VECMag(&aimVel) == 0.0f) {
        aimVel = (HuVecF){ 1.0f, 1.0f, 1.0f };
    }
    VECNormalize(&aimVel, &aimDir);
    if (VECMag(&diff) == 0.0f) {
        diff = (HuVecF){ 1.0f, 1.0f, 1.0f };
    }
    VECNormalize(&diff, &diff);
    VECScale(&diff, &lead, -1.0f);
    dot1 = VECDotProduct(&aimDir, &diff);
    dot2 = VECDotProduct(&front, &lead);
    com->unk34++;
    if ((machine->gunNo == 1 || machine->gunNo == 6) && com->unk40 != 5) {
        HuPadBtn[machine->unk348] |= PAD_BUTTON_B;
    }
    if (machine->gunNo == 12) {
        if (com->unk40 == 5) {
            if (com->unk34 % 180 == 0) {
                HuPadBtnDown[machine->unk348] |= PAD_BUTTON_B;
            }
        } else if (com->unk40 >= 3) {
            if (com->unk34 % 30 == 0) {
                HuPadBtnDown[machine->unk348] |= PAD_BUTTON_B;
            }
        } else {
            HuPadBtnDown[machine->unk348] |= PAD_BUTTON_B;
        }
    }
    if (machine->gunNo == 10) {
        bullet = machine->gun->bullet;
        if (bullet->mode != 0) {
            HuPadBtn[machine->unk348] |= PAD_BUTTON_B;
            VECSubtract(&bullet->pos, &aimPos, &diff);
            if (VECMag(&diff) <= 600.0f) {
                HuPadBtn[machine->unk348] &= ~PAD_BUTTON_B;
            }
        } else if (dist < 600.0f && !(HuPadBtn[machine->unk348] & PAD_BUTTON_B)) {
            HuPadBtnDown[machine->unk348] |= PAD_BUTTON_B;
            HuPadBtn[machine->unk348] |= PAD_BUTTON_B;
        }
    }
    if (machine->gunNo == 2 || machine->gunNo == 5) {
        bullet = machine->gun->unk34;
        if (bullet != 0 && bullet->mode != 0) {
            HuPadBtn[machine->unk348] |= PAD_BUTTON_B;
            VECSubtract(&aimPos, &bullet->unk104, &diff);
            angle = VECMag(&diff);
            VECSubtract(&bullet->unk110, &bullet->unk104, &diff);
            angle2 = VECMag(&diff);
            if (angle2 >= angle) {
                HuPadBtn[machine->unk348] &= ~PAD_BUTTON_B;
            }
        }
    }
    if (dist < 600.0f && machine->gunNo == 2 && !(HuPadBtn[machine->unk348] & PAD_BUTTON_B)) {
        HuPadBtnDown[machine->unk348] |= PAD_BUTTON_B;
        HuPadBtn[machine->unk348] |= PAD_BUTTON_B;
    }
    com->unk30 = 0;
    stepLen = (machine->unk28 == 1) ? 150.0f : ((machine->unk28 == 2) ? 200.0f : 100.0f);
    if ((sys->stageNo == 0 || sys->stageNo == 7) && (machine->unk368 & 0x50) == 0) {
        for (i = 0; i < 3; i++) {
            VECScale(&front, &dir, machine->unk358 + stepLen * (machine->unk288 + 3));
            if (i == 0) {
                VECScale(&side, &ofs, machine->unk358);
                VECAdd(&dir, &ofs, &dir);
            } else if (i == 2) {
                VECScale(&side, &ofs, -machine->unk358);
                VECAdd(&dir, &ofs, &dir);
            }
            VECAdd(&dir, &machine->pos, &dir);
            if (SdStageDistCalc(dir) < SdStageRadiusCalc()) {
                hit[i] = 1;
            }
        }
        for (i = 0; i < 2; i++) {
            if (i == 0) {
                VECScale(&side, &dir, 400.0f + machine->unk358);
            } else {
                VECScale(&side, &dir, -(400.0f + machine->unk358));
            }
            VECAdd(&dir, &machine->pos, &dir);
            angle = SdStageDistCalc(dir);
            if (angle < SdStageRadiusCalc() || -10000.0f == angle) {
                hit[i + 3] = 1;
            }
        }
    }
    angle = ComObjDistGet(machine, front);
    if (-10000.0f != angle) {
        if (angle >= 0.0f) {
            hit[0] = 1;
        } else {
            hit[2] = 1;
        }
    }
    if (hit[3] != 0) {
        com->unk30 = 1;
    } else if (hit[4] != 0) {
        com->unk30 = 2;
    } else if (hit[0] != 0 && hit[2] != 0) {
        com->unk30 = 1;
    } else if (hit[0] != 0) {
        com->unk30 = 1;
    } else if (hit[2] != 0) {
        com->unk30 = 2;
    }
    if (com->unk38 == 7) {
        com->unk30 = 0;
    }
    if (com->unk38 == 8 && dist < 150.0f) {
        com->unk30 = 0;
    }
    if (com->unk30 == 1) {
        HuPadStkX[machine->unk348] = 56;
    }
    if (com->unk30 == 2) {
        HuPadStkX[machine->unk348] = -56;
    }
    angle = VECMag(&aimVel);
    if (angle > 0.1f) {
        if (com->unk40 <= 2) {
            angle *= dist / (5.0f * machine->gun->bullet->param->unk8);
            VECNormalize(&aimVel, &lead);
            if (machine->gunNo != 2) {
                VECScale(&lead, &lead, angle);
            } else {
                VECScale(&lead, &lead, angle + rand8() % 30);
            }
            VECAdd(&aimPos, &lead, &lead);
        } else {
            lead = aimPos;
        }
    } else {
        lead = aimPos;
    }
    VECSubtract(&machine->pos, &lead, &lead);
    lead.y = 0.0f;
    if (VECMag(&lead) == 0.0f) {
        lead = (HuVecF){ 1.0f, 1.0f, 1.0f };
    }
    VECNormalize(&lead, &lead);
    angle = HuAtan(back.x, back.z);
    MTXRotRad(rotMtx, 'y', MTXDegToRad(-angle));
    MTXMultVec(rotMtx, &lead, &lead);
    angle = HuAtan(lead.x, lead.z);
    if (machine->gunNo == 12 && dist < 600.0f) {
        angle += 180.0f;
        if (angle > 180.0f) {
            angle -= 360.0f;
        }
    }
    if (sys->gameType == 0 && (machine->gunNo == 3 || machine->gunNo == 9)) {
        if (machine->gunNo == 3) {
            if (com->unk40 <= 3) {
                if (dist >= 1000.0f) {
                    tol = 10.0f;
                } else {
                    tol = 5.0f;
                }
            } else {
                tol = 2.0f;
            }
        } else if (com->unk40 <= 3) {
            if (dist >= 1000.0f) {
                tol = 45.0f;
            } else {
                tol = 10.0f;
            }
        } else {
            tol = 2.0f;
        }
    } else if (machine->gunNo == 4) {
        if (sys->gameType == 1 && com->unk38 == 7) {
            tol = 2.0f;
        } else {
            tol = 15.0f;
        }
    } else if (sys->gameType != 1 || com->unk38 != 8) {
        tol = 2.0f;
    } else {
        tol = 0.5f;
    }
    if (dist < 600.0f) {
        tol += (60.0f * (600.0f - dist)) / 600.0f;
        if (tol > 60.0f) {
            tol = 60.0f;
        }
    }
    fire = 0;
    time = com->unk34 % 180;
    if (com->unk40 == 5) {
        if (time < 60) {
            fire = 1;
        }
    } else if (com->unk40 == 4) {
        if (time < 90) {
            fire = 1;
        }
    } else if (com->unk40 == 3) {
        if (time < 120) {
            fire = 1;
        }
    } else if (com->unk40 == 2) {
        if (time < 150) {
            fire = 1;
        }
    } else {
        fire = 1;
    }
    if (angle <= tol && angle >= -tol && fire == 1 && !(HuPadBtn[machine->unk348] & PAD_BUTTON_B)) {
        HuPadBtnDown[machine->unk348] |= PAD_BUTTON_B;
        HuPadBtn[machine->unk348] |= PAD_BUTTON_B;
    }
    VECSubtract(&machine->pos, &goal, &diff);
    if (VECMag(&diff) <= 200.0f) {
        diff = lead;
    }
    angle = HuAtan(back.x, back.z);
    MTXRotRad(rotMtx, 'y', MTXDegToRad(-angle));
    MTXMultVec(rotMtx, &diff, &diff);
    angle = HuAtan(diff.x, diff.z);
    if (angle >= tol) {
        if (com->mode != 1) {
            com->mode = 1;
            com->unk8 = 30.0f + 0.25f * com->unk40;
            com->unk4 = 0;
        }
    } else if (angle <= -tol) {
        if (com->mode != 2) {
            com->mode = 2;
            com->unk8 = 30.0f + 0.25f * com->unk40;
            com->unk4 = 0;
        }
    } else {
        com->mode = 0;
        com->unk8 = com->unk4 = 0;
    }
    if (++com->unk4 >= com->unk8 && com->unk30 == 0) {
        switch (com->mode) {
            case 0:
                com->unkC *= 0.9f;
                break;
            case 1:
                com->unkC -= 8.0f;
                break;
            case 2:
                com->unkC += 8.0f;
                break;
        }
        limit = (machine->unk3C8 < 3) ? 60.0f - 4.0f * (3 - machine->unk3C8) : 60.0f;
        com->unkC = (com->unkC > limit) ? limit : ((com->unkC < -limit) ? -limit : com->unkC);
        HuPadStkX[machine->unk348] = com->unkC;
    }
    fire = -1;
    if (machine->mode == 3) {
        if (machine->unk4 == 0) {
            if (sys->stageNo == 0) {
                if (com->unk38 == 8 && dist < 1000.0f) {
                    VECSubtract(&machine->pos, &goal, &dir);
                } else {
                    angle = 10000.0f;
                    fire = -1;
                    for (i = 0; i < 5; i++) {
                        if (-10000.0f != sys->unkA34[i].x) {
                            VECSubtract(&machine->pos, &sys->unkA34[i], &diff);
                            angle2 = VECMag(&diff);
                            if (angle > angle2) {
                                angle = angle2;
                                fire = i;
                                dir = diff;
                            }
                        }
                    }
                }
            } else if (sys->stageNo == 7) {
                dir = machine->pos;
                if (VECMag(&machine->pos) >= 1500.0f) {
                    VECScale(&dir, &dir, -1.0f);
                }
                if (VECMag(&dir) == 0.0f) {
                    dir = (HuVecF){ 1.0f, 1.0f, 1.0f };
                }
                VECNormalize(&dir, &dir);
            }
            if (VECMag(&dir) == 0.0f) {
                dir = (HuVecF){ 1.0f, 1.0f, 1.0f };
            }
            VECNormalize(&dir, &dir);
            angle = HuAtan(dir.x, dir.z);
            angle2 = HuAtan(front.x, front.z);
            angle -= angle2;
            if (angle > 180.0f) {
                angle -= 360.0f;
            }
            if (angle < -180.0f) {
                angle = 360.0f + angle;
            }
            com->unk44 = -56.0 * HuSin(angle);
            com->unk4C = 56.0 * HuCos(angle);
        } else {
            HuPadStkX[machine->unk348] = com->unk44;
            HuPadStkY[machine->unk348] = com->unk4C;
        }
    }
}

/* 270 insns */
static float ComObjDistGet(SDMACHINE *machine, HuVecF dir)
{
    HuVecF diff;
    HuVecF diffCopy;
    HuVecF pos = machine->pos;
    s32 level;
    SDCOMWORK *com = &machine->com;
    float cosWide;
    float range;
    float cosLimit;
    float dist;
    float dirAngle;
    float cosNarrow;
    s32 i;
    SDSTAGEOBJ *obj;

    level = 7 - com->unk40;
    cosWide = 12.0f * level;
    if (sys->stageObj == 0) {
        return 0.0f;
    }
    cosWide = HuCos(cosWide);
    cosNarrow = cos(1.3089969389957472);
    dir.y = 0.0f;
    if (VECMag(&dir) == 0.0f) {
        dir = (HuVecF){ 1.0f, 1.0f, 1.0f };
    }
    VECNormalize(&dir, &dir);
    for (i = 0; i < 8; i++) {
        obj = &sys->stageObj[i];
        if (obj->mdlId == -1 || obj->unk5C == 0 || obj->type == 4 || obj->type == 5) {
            continue;
        }
        if (obj->type == 0) {
            range = 150.0f + machine->unk358;
            cosLimit = cosNarrow;
        } else {
            range = machine->unk358 + 100.0f * level;
            cosLimit = cosWide;
        }
        VECAdd(&obj->pos, (HuVecF *)&obj->unk64->unk4, &diff);
        VECSubtract(&diff, &pos, &diff);
        diffCopy = diff;
        if (obj->unk64->unk0 == 1) {
            diff.y = 0.0f;
        }
        dist = VECMag(&diff);
        if (dist > range + obj->unk34.x) {
            continue;
        }
        if (VECMag(&diff) == 0.0f) {
            diff = (HuVecF){ 1.0f, 1.0f, 1.0f };
        }
        VECNormalize(&diff, &diff);
        if (VECDotProduct(&dir, &diff) < cosLimit) {
            continue;
        }
        dist = HuAtan(diff.x, diff.z);
        dirAngle = HuAtan(dir.x, dir.z);
        dist -= dirAngle;
        if (dist > 180.0f) {
            dist -= 360.0f;
        }
        if (dist < -180.0f) {
            dist = 360.0f + dist;
        }
        return dist;
    }
    return -10000.0f;
}

/* 257 insns */
static s32 ComNextModeFarGet(SDMACHINE *machine)
{
    SDCOMWORK *com = &machine->com;
    SDMACHINE *enemy = machine->enemy;
    /* retail: both divide by the enemy's unk3D4 */
    s32 life = machine->unkE4 / enemy->unk3D4;
    s32 enemyLife = enemy->unkE4 / enemy->unk3D4;
    s32 chance;

    if (GwPlayerConf[enemy->playerNo].type == GW_TYPE_MAN) {
        if (com->unk40 == 5) {
            if (enemy->unk330 != 0) {
                return 4;
            }
            if (com->unk34 % 180 == 0) {
                chance = rand8() % 100;
                if (chance < 15) {
                    return 1;
                }
                if (chance < 45) {
                    return 0;
                }
                if (chance < 90) {
                    return 4;
                }
                return 3;
            }
            return com->unk38;
        } else if (com->unk40 == 3) {
            if (enemy->unk330 != 0) {
                return 4;
            }
            if (com->unk34 % 180 == 0) {
                chance = rand8() % 100;
                if (chance < 20) {
                    return 4;
                }
                if (chance < 25) {
                    return 3;
                }
            } else if (com->unk38 == 4 || com->unk38 == 3) {
                return com->unk38;
            }
        } else if (com->unk40 == 2) {
            if (com->unk34 % 180 == 0) {
                chance = rand8() % 100;
                if (chance < 10) {
                    return 4;
                }
            } else if (com->unk38 == 4) {
                return com->unk38;
            }
        }
    } else if (com->unk38 == 4) {
        if (com->unk34 % 30 != 0) {
            return com->unk38;
        }
    } else if (com->unk34 % 240 == 0) {
        return 4;
    }
    if (life > enemyLife) {
        return 1;
    }
    if (life == enemyLife && enemy->unk210 == 0 && machine->unk210 != 0) {
        if (com->unk40 < 3) {
            return 1;
        } else {
            return 2;
        }
    }
    if (enemy->mode >= 2 || enemy->unk210 != 0) {
        if (com->unk40 < 3) {
            return 2;
        } else {
            return 1;
        }
    }
    if (machine->unk210 != 0) {
        if (com->unk40 <= 3) {
            return 1;
        } else {
            return 2;
        }
    }
    if ((machine->gunNo == 6 || machine->gunNo == 11) && enemy->gunNo != 6 && enemy->gunNo != 11 && machine->unkE4 > 4) {
        return 7;
    }
    if (machine->unk28C > enemy->unk28C && machine->unk288 < enemy->unk288) {
        if (enemy->gunNo == 12) {
            return 5;
        } else {
            return 6;
        }
    }
    return 1;
}

/* 111 insns */
static s32 ComNextModeNearGet(SDMACHINE *machine)
{
    SDCOMWORK *com = &machine->com;
    SDMACHINE *enemy = machine->enemy;
    s32 chance;

    if (GwPlayerConf[enemy->playerNo].type == GW_TYPE_MAN) {
        if (com->unk34 % 60 == 0) {
            chance = rand8() % 100;
            if (com->unk40 == 5) {
                if (chance < 80) {
                    return 4;
                } else {
                    return 8;
                }
            } else if (com->unk40 == 3) {
                if (chance < 20) {
                    return 4;
                } else {
                    return 8;
                }
            } else if (com->unk40 == 2) {
                if (chance < 10) {
                    return 4;
                } else {
                    return 8;
                }
            }
        } else if (com->unk40 != 1) {
            return com->unk38;
        }
    } else if (com->unk38 == 4) {
        if (com->unk34 % 30 != 0) {
            return com->unk38;
        }
    } else if (com->unk34 % 240 == 0) {
        return 4;
    }
    return 8;
}

/* 109 insns */
static HuVecF ComStageObjPosGet(SDMACHINE *machine)
{
    s32 i;
    SDCOMWORK *com = &machine->com;
    SDMACHINE *enemy = machine->enemy;
    SDSTAGEOBJ *nearObj = NULL;
    HuVecF defPos = { -10000.0f, 0.0f, 0.0f };
    s32 nearNo = 10000;
    float nearDist = 10000.0f;
    HuVecF diff;
    float dist;
    SDSTAGEOBJ *obj;

    if (enemy->unk3D4 == 1) {
        return enemy->pos;
    }
    if (sys->stageObj != 0) {
        for (i = 0; i < 8; i++) {
            obj = &sys->stageObj[i];
            if (obj->mdlId == -1 || obj->unk5C == 0 || obj->type >= 4 || obj->unk64->unk28 == 0 || nearNo < obj->unk64->unk28) {
                continue;
            }
            VECSubtract(&machine->pos, &obj->pos, &diff);
            dist = VECMag(&diff);
            if (nearDist < dist) {
                continue;
            }
            nearDist = dist;
            nearNo = obj->unk64->unk28;
            nearObj = obj;
        }
    }
    if (nearObj != 0) {
        return nearObj->pos;
    } else {
        return defPos;
    }
}

/* 98 insns */
static void ComRandomizeMachine(SDMACHINE *machine, s32 a1, s32 a2, s32 a3)
{
    SdMachineParamSet(machine, machine->tireNo, machine->bodyNo, machine->unk3C0, machine->gunNo);
    machine->unk3CC += a1;
    machine->unk3C8 += a2;
    machine->unk3D0 += a3;
    machine->unk3C8 = (machine->unk3C8 > 8) ? 8 : ((machine->unk3C8 < 1) ? 1 : machine->unk3C8);
    machine->unk3CC = (machine->unk3CC > 8) ? 8 : ((machine->unk3CC < 1) ? 1 : machine->unk3CC);
    machine->unk3D0 = (machine->unk3D0 > 8) ? 8 : ((machine->unk3D0 < 1) ? 1 : machine->unk3D0);
    machine->unk3D4 = (machine->unk3D4 > 8) ? 8 : ((machine->unk3D4 < 1) ? 1 : machine->unk3D4);
    machine->unk3D8 = (machine->unk3D8 > 8) ? 8 : ((machine->unk3D8 < 1) ? 1 : machine->unk3D8);
}
