/*
 * m565dll ending.c -- written 2026-09-23 (W1 forks; see NOTES.md). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m565dll/asm/REL/m565dll/ending.s.
 */

#include "REL/m565dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/flag.h"
#include "game/gamemes.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x3A8 */ /* s32 lbl_1_rodata_3A8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x3B4 */ /* s32 lbl_1_rodata_3B4[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x3C0 */ /* float lbl_1_rodata_3C0 = -300.0f; */
/* 0x3C4 */ /* float lbl_1_rodata_3C4 = -9499.99f; */
/* 0x3C8 */ /* float lbl_1_rodata_3C8 = 0.0f; */
/* 0x3CC */ /* float lbl_1_rodata_3CC = 1.0f; */
/* 0x3D0 */ /* float lbl_1_rodata_3D0 = 150.0f; */
/* 0x3D8 */ /* double lbl_1_rodata_3D8 = 3.141592653589793; */
/* 0x3E0 */ /* double lbl_1_rodata_3E0 = 180; */
/* 0x3E8 */ /* float lbl_1_rodata_3E8 = 5.0f; */
/* 0x3EC */ /* float lbl_1_rodata_3EC = 4.0f; */
/* 0x3F0 */ /* float lbl_1_rodata_3F0 = 180.0f; */
/* 0x3F4 */ /* float lbl_1_rodata_3F4 = 360.0f; */
/* 0x3F8 */ /* float lbl_1_rodata_3F8 = -180.0f; */
/* 0x3FC */ /* float lbl_1_rodata_3FC = 3.0f; */
/* 0x400 */ /* float lbl_1_rodata_400 = 0.9f; */
/* 0x404 */ /* float lbl_1_rodata_404 = 8.0f; */
/* 0x408 */ /* float lbl_1_rodata_408 = 100.0f; */
/* 0x40C */ /* float lbl_1_rodata_40C = 0.1f; */
/* 0x410 */ /* float lbl_1_rodata_410 = -1.0f; */
/* 0x414 */ /* float lbl_1_rodata_414 = 0.04f; */
/* 0x418 */ /* float lbl_1_rodata_418 = 1000.0f; */
/* 0x41C */ /* float lbl_1_rodata_41C = 900.0f; */
/* 0x420 */ /* double lbl_1_rodata_420 = 4503601774854144; */

/* --- .data --- */
/* 0xC08 jumptable_1_data_C08: the switch in fn_1_EE4C */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x789C */ HuVecF lbl_1_bss_789C; /* camera target: mean of the survivors' positions, y = 150 */
/* 0x7898 */ float lbl_1_bss_7898;  /* CZoom at the start of the ending */
/* 0x7894 */ float lbl_1_bss_7894;  /* largest survivor XZ distance from lbl_1_bss_789C */
/* 0x7890 */ s32 lbl_1_bss_7890;    /* all four players turned to face the camera (flag, not a pointer) */

/* --- functions (reference order) --- */
#define M565_ANGLE_WRAP(a) ((a) > 180.0f ? (a) - 360.0f : ((a) <= -180.0f ? 360.0f + (a) : (a)))
#define M565_ABS(a) (((a) >= 0.0f) ? (a) : -(a))

/* fn_1_EE4C, ending.c, 924 insns. Ending sequence; returns 1 when done. */
s32 fn_1_EE4C(M565_WORK *work)
{
    s32 done;
    M565_OBJECT *obj = &work->unk018;
    M565_STAGE *stage = &obj->unk2E4;
    M565_PUKU2 *puku2 = &obj->unk3648;
    M565_BACK *back = &obj->unk2B8;
    s32 i;
    s32 j;
    s32 busy;
    s32 winNum;
    s16 turned;
    M565_PLAYER *player;
    M565_PLAYER *player1;
    M565_PLAYER *player2;
    HuVecF *vecP;
    float dot;
    float angle;
    float rad;
    float rad2;
    float dist;
    float target;
    HuVecF diff;
    HuVecF dir;
    HuVecF fwd;
    s16 winner[4];

    done = 0;
    switch (work->unk00E) {
    case 0:
        if (stage->unk30D0 == 0 && puku2->unk1D0 == 0) {
            busy = 0;
            for (i = 0; i < 4; i++) {
                player = &obj->unk008[i];
                if (player->unk074->y < -300.0f) {
                    if (player->unk074->y > -9499.99f) {
                        busy = 1;
                    }
                } else {
                    if (M565_ABS(player->unk004->actor->velY) > 0.0f) {
                        busy = 1;
                    }
                }
                MgPlayerVibrateKill(player->unk004);
            }
            if (!busy) {
                work->unk014 = 0;
                work->unk00E++;
            }
        }
        break;
    case 1:
        winNum = 0;
        {
            HuVecF zero = { 0.0f, 0.0f, 0.0f };
            vecP = &zero;
            lbl_1_bss_789C = *vecP;
        }
        for (i = 0; i < 4; i++) {
            player = &obj->unk008[i];
            fn_1_8984(player, 0);
            Hu3DMotionSet(player->unk010, player->unk012[0]);
            Hu3DModelAttrSet(player->unk010, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(player->unk010, HU3D_ATTR_DISPOFF);
            Hu3DModelScaleSet(player->unk010, 1.0f, 1.0f, 1.0f);
            if (player->unk074->y > -300.0f && player->unk090 == 0) {
                player->unk098 = 1;
                PSVECAdd(&lbl_1_bss_789C, player->unk074, &lbl_1_bss_789C);
                winNum++;
            }
            CharModelVoiceVolSet(player->unk00C, 127);
        }
        if (winNum == 0) {
            work->unk00E = 10;
            break;
        }
        lbl_1_bss_789C.x = lbl_1_bss_789C.x / winNum;
        lbl_1_bss_789C.y = 150.0f;
        lbl_1_bss_789C.z /= winNum;
        lbl_1_bss_7894 = 0.0f;
        for (i = 0; i < 4; i++) {
            player = &obj->unk008[i];
            dir.x = sin(M_PI * player->unk078->y / 180.0);
            dir.y = 0.0f;
            dir.z = cos(M_PI * player->unk078->y / 180.0);
            fwd.x = 0.0f;
            fwd.y = 0.0f;
            fwd.z = 1.0f;
            PSVECNormalize(&fwd, &fwd);
            dot = PSVECDotProduct(&dir, &fwd);
            rad = acos(dot);
            angle = 180.0 * (rad / M_PI);
            if (M565_ABS(angle) > 5.0f && player->unk098) {
                Hu3DMotionShiftSet(player->unk010, player->unk012[1], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            }
            player->unk07C = M565_ANGLE_WRAP(Hu3DData[player->unk010].rot.y);
            if (player->unk098) {
                PSVECSubtract(player->unk074, &lbl_1_bss_789C, &diff);
                diff.y = 0.0f;
                dist = PSVECMag(&diff);
                if (lbl_1_bss_7894 < dist) {
                    lbl_1_bss_7894 = dist;
                }
            }
        }
        Hu3DModelAttrReset(back->unk01C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk01E, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk022, HU3D_ATTR_DISPOFF);
        {
            HuVecF shake = { 0.0f, 0.0f, 0.0f };
            HuVecF *vecP2;
            vecP2 = &shake;
            obj->unk3838 = *vecP2;
        }
        lbl_1_bss_7898 = CZoom;
        lbl_1_bss_7890 = 0;
        work->unk014 = 0;
        work->unk00E++;
        break;
    case 2:
        if (lbl_1_bss_7890 == 0) {
            turned = 0;
            for (i = 0; i < 4; i++) {
                player = &obj->unk008[i];
                dir.x = sin(M_PI * player->unk07C / 180.0);
                dir.y = 0.0f;
                dir.z = cos(M_PI * player->unk07C / 180.0);
                fwd.x = 0.0f;
                fwd.y = 0.0f;
                fwd.z = 1.0f;
                PSVECNormalize(&fwd, &fwd);
                dot = PSVECDotProduct(&dir, &fwd);
                rad2 = acos(dot);
                angle = 180.0 * (rad2 / M_PI);
                target = 180.0 * (atan2(fwd.x, fwd.z) / M_PI);
                target = M565_ANGLE_WRAP(target);
                if (M565_ABS(angle) > 3.0f) {
                    player->unk07C = fn_1_8F4(target, player->unk07C, 0.9f);
                } else {
                    Hu3DMotionShiftSet(player->unk010, player->unk012[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    player->unk004->actor->rotY = target;
                    player->unk07C = target;
                    turned++;
                }
                Hu3DModelRotSet(player->unk010, 0.0f, player->unk07C, 0.0f);
            }
            if (turned >= 4) {
                lbl_1_bss_7890 = 1;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                player1 = &obj->unk008[i];
                player2 = &obj->unk008[j];
                if (i == j || !player1->unk098 || !player2->unk098) {
                    continue;
                }
                PSVECSubtract(player1->unk074, player2->unk074, &diff);
                diff.y = 0.0f;
                dist = PSVECMag(&diff);
                if (dist < 100.0f) {
                    PSVECScale(&diff, &diff, 0.1f);
                    PSVECAdd(player1->unk074, &diff, player1->unk074);
                    PSVECScale(&diff, &diff, -1.0f);
                    PSVECAdd(player2->unk074, &diff, player2->unk074);
                }
            }
        }
        PSVECSubtract(&lbl_1_bss_789C, &obj->unk382C, &diff);
        obj->unk382C.x += 0.04f * diff.x;
        obj->unk382C.y += 0.04f * diff.y;
        obj->unk382C.z += 0.04f * diff.z;
        dist = 1000.0f - lbl_1_bss_7894;
        CZoom += 0.04f * ((lbl_1_bss_7898 - dist) - CZoom);
        CRot.x += 0.04f * -CRot.x;
        if (work->unk014++ >= 60) {
            Hu3DModelAttrReset(back->unk020, HU3D_ATTR_DISPOFF);
            Hu3DMotionShapeTimeSet(back->unk020, 0.0f);
            Hu3DModelPosSet(back->unk020, obj->unk382C.x, 0.0f, obj->unk382C.z - 900.0f);
            work->unk00E++;
        }
        break;
    case 3:
        for (i = 0; i < 4; i++) {
            winner[i] = -1;
            player = &obj->unk008[i];
            if (player->unk098) {
                winner[i] = player->unk00C;
                Hu3DMotionShiftSet(player->unk010, player->unk012[5], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
                Hu3DModelAttrReset(player->unk010, HU3D_MOTATTR_LOOP);
                GWMgCoinBonusSet(player->unk008, 10);
            }
        }
        work->unk3874 = GameMesMgWinnerCreate(winner[0], winner[1], winner[2], winner[3]);
        work->unk014 = 0;
        work->unk00E++;
        break;
    case 4:
        if (work->unk3878 < 0) {
            work->unk3878 = fn_1_DF0(0x79);
        }
        if (++work->unk014 >= 209) {
            work->unk3874 = -1;
            work->unk014 = 0;
            work->unk00E = 12;
        }
        break;
    case 10:
        work->unk3874 = GameMesMgDrawCreate();
        work->unk014 = 0;
        work->unk00E++;
        break;
    case 11:
        if (work->unk3878 < 0) {
            work->unk3878 = fn_1_DF0(0x7B);
        }
        if (work->unk014 == 0) {
            CharLoseVoicePlay(-1, -1, -1, -1);
        }
        if (++work->unk014 >= 209) {
            work->unk3874 = -1;
            work->unk014 = 0;
            work->unk00E++;
        }
        break;
    case 12:
        work->unk014 = 0;
        done = 1;
        break;
    }
    return done;
}
