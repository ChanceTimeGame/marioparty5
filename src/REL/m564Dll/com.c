/*
 * m564dll com.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m564Dll/asm/REL/m564Dll/com.s.
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

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x270 */ /* s16 lbl_1_rodata_270[4] = { 0x0064, 0x0050, 0x003C, 0x0028 }; */
/* 0x278 */ /* s32 lbl_1_rodata_278[4] = { 0x00000050, 0x00000055, 0x0000005A, 0x00000064 }; */
/* 0x288 */ /* float lbl_1_rodata_288 = 170.0f; */
/* 0x28C */ /* float lbl_1_rodata_28C = 450.0f; */
/* 0x290 */ /* double lbl_1_rodata_290 = 180; */
/* 0x298 */ /* double lbl_1_rodata_298 = 3.141592653589793; */
/* 0x2A0 */ /* float lbl_1_rodata_2A0 = 20.0f; */
/* 0x2A4 */ /* s16 lbl_1_rodata_2A4[4] = { 0x0078, 0x006E, 0x0064, 0x005A }; */
/* 0x2AC */ /* float lbl_1_rodata_2AC = 9999.9f; */
/* 0x2B0 */ /* float lbl_1_rodata_2B0 = 120.0f; */
/* 0x2B4 */ /* float lbl_1_rodata_2B4 = 100.0f; */
/* 0x2B8 */ /* float lbl_1_rodata_2B8 = 101.0f; */
/* 0x2BC */ /* s32 lbl_1_rodata_2BC[4] = { 0x3F4CCCCD, 0x3F666666, 0x3F800000, 0x3F800000 }; */
/* 0x2CC */ /* float lbl_1_rodata_2CC = 10.0f; */
/* 0x2D0 */ /* double lbl_1_rodata_2D0 = 15; */
/* 0x2D8 */ /* float lbl_1_rodata_2D8 = 0.0f; */
/* 0x2DC */ /* float lbl_1_rodata_2DC = 15.0f; */
/* 0x2E0 */ /* float lbl_1_rodata_2E0 = 56.0f; */
/* 0x2E8 */ /* double lbl_1_rodata_2E8 = 550; */
/* 0x2F0 */ /* float lbl_1_rodata_2F0 = 150.0f; */
/* 0x2F4 */ /* float lbl_1_rodata_2F4 = 425.0f; */
/* 0x2F8 */ /* s32 lbl_1_rodata_2F8[4] = { 0x00000000, 0x0000001E, 0x0000003C, 0x00000064 }; */
/* 0x308 */ /* s32 lbl_1_rodata_308[4] = { 0x0000003C, 0x00000050, 0x0000005A, 0x00000064 }; */
/* 0x318 */ /* s32 lbl_1_rodata_318[4] = { 0x0000002D, 0x0000001E, 0x0000000A, 0x00000000 }; */
/* 0x328 */ /* float lbl_1_rodata_328 = 400.0f; */
/* 0x32C */ /* float lbl_1_rodata_32C = 1.0f; */
/* 0x330 */ /* float lbl_1_rodata_330 = -1.0f; */

/* --- functions (reference order) --- */
/* fn_1_9AC0 com 7 */
void fn_1_9AC0(M564_PLAYER *player)
{
    player->unk058 = 0;
    player->unk05C = -1;
    player->unk05E = -1;
}

/* fn_1_9ADC com 73 */
void fn_1_9ADC(M564_PLAYER *player)
{
    s16 fuseTbl[4] = { 100, 80, 60, 40 };

    if (player->unk02C->mode == 0) {
        if (player->unk034 != 0 && lbl_1_bss_1E8[player->unk038]->unk022 < fuseTbl[player->dif]) {
            player->unk06C = PAD_BUTTON_A;
            fn_1_9C00(player, 0);
        } else {
            switch (player->unk058) {
                case 0:
                    fn_1_9C20(player);
                    break;
                case 1:
                    fn_1_9D28(player);
                    break;
                case 2:
                    fn_1_9D90(player);
                    break;
                case 3:
                    fn_1_9E30(player);
                    break;
                case 4:
                    fn_1_9EB8(player);
                    break;
            }
        }
    }
}

/* fn_1_9C00 com 8 */
void fn_1_9C00(M564_PLAYER *player, s16 mode)
{
    if (mode != player->unk058) {
        player->unk058 = mode;
        player->unk060 = 0;
    }
}

/* fn_1_9C20 com 66 */
void fn_1_9C20(M564_PLAYER *player)
{
    if (fn_1_AD38(player)) {
        fn_1_9C00(player, 3);
        return;
    }
    if (fn_1_B00C(player)) {
        fn_1_9C00(player, 2);
        return;
    }
    if (fn_1_B2DC(player)) {
        fn_1_9C00(player, 1);
        return;
    }
    if (player->unk034 != 0) {
        fn_1_A008(player);
        return;
    }
    player->unk05C = fn_1_A38C(player);
    if (player->unk05C != -1) {
        fn_1_9C00(player, 4);
        return;
    }
}

/* fn_1_9D28 com 26 */
void fn_1_9D28(M564_PLAYER *player)
{
    player->unk060++;
    fn_1_A8D8(player, 1);
    if (player->unk060 >= 30) {
        fn_1_9C00(player, 0);
    }
}

/* fn_1_9D90 com 40 */
void fn_1_9D90(M564_PLAYER *player)
{
    HuVecF pos;

    player->unk060++;
    if (player->unk060 >= 10) {
        if (fn_1_902C(&player->pos, &pos)) {
            player->unk040 = pos;
            player->unk060 = 0;
        } else {
            fn_1_9C00(player, 0);
        }
    }
    fn_1_A8D8(player, 1);
}

/* fn_1_9E30 com 34 */
void fn_1_9E30(M564_PLAYER *player)
{
    if (!fn_1_AD38(player)) {
        fn_1_9C00(player, 0);
        return;
    }
    if (fn_1_A8D8(player, 1)) {
        fn_1_9C00(player, 0);
    }
}

/* fn_1_9EB8 com 84 */
void fn_1_9EB8(M564_PLAYER *player)
{
    s16 bombNo;

    if (player->dif >= 2) {
        if (fn_1_AD38(player)) {
            fn_1_9C00(player, 3);
            return;
        }
        if (fn_1_B00C(player)) {
            fn_1_9C00(player, 2);
            return;
        }
    }
    if (!fn_1_8D60(player->unk05C)) {
        fn_1_9C00(player, 0);
        return;
    }
    bombNo = fn_1_8340(&player->pos, player->unk02C->actor->rotY);
    MgActorPosGet(lbl_1_bss_1E8[player->unk05C]->unk000, &player->unk040);
    if (bombNo != -1) {
        player->unk05C = -1;
        player->unk06C = PAD_BUTTON_A;
        fn_1_9C00(player, 0);
        return;
    }
    fn_1_A8D8(player, 0);
}

/* fn_1_A008 com 132 */
void fn_1_A008(M564_PLAYER *player)
{
    s32 rateTbl[4] = { 80, 85, 90, 100 };
    HuVecF dir;
    float dist;
    float angle;

    if (player->unk05E == -1) {
        player->unk05E = fn_1_A594(player);
    }
    if (player->unk05E != -1) {
        player->unk040 = lbl_1_bss_100[player->unk05E]->pos;
        dist = fn_1_13F0(&player->pos, &player->unk040, &dir);
        if (dist >= 170.0f && dist <= 450.0f) {
            angle = (atan2(dir.x, dir.z) / M_PI) * 180.0;
            angle = fabs(fn_1_1338(player->unk02C->actor->rotY, angle));
            if (angle < 20.0f && fn_1_A678(player) && (int)frandmod(100) < rateTbl[player->dif]) {
                player->unk06C = PAD_BUTTON_A;
                player->unk05E = -1;
                return;
            }
            fn_1_A8D8(player, 0);
        }
        if (dist > 450.0f) {
            fn_1_A8D8(player, 0);
        }
    }
}

/* fn_1_A218 com 93 */
int fn_1_A218(M564_PLAYER *player, s16 bombNo)
{
    s16 fuseTbl[4] = { 120, 110, 100, 90 };
    float dist;
    float otherDist;
    int i;

    if (!fn_1_8D60(bombNo)) {
        return 0;
    }
    if (lbl_1_bss_1E8[bombNo]->unk022 < fuseTbl[player->dif]) {
        return 0;
    }
    dist = fn_1_13A4(&player->pos, &lbl_1_bss_1E8[bombNo]->unk040);
    for (i = 0; i < 4; i++) {
        if (player->no != i && !fn_1_5E5C(i)) {
            otherDist = fn_1_13A4(&lbl_1_bss_100[i]->pos, &lbl_1_bss_1E8[bombNo]->unk040);
            if (otherDist < dist) {
                return 0;
            }
        }
    }
    return 1;
}

/* fn_1_A38C com 130 */
s16 fn_1_A38C(M564_PLAYER *player)
{
    float dist;
    s16 result = -1;
    float minDist = 9999.9f;
    int i;
    HuVecF pos;

    for (i = 0; i < 15; i++) {
        if (fn_1_A218(player, i)) {
            MgActorPosGet(lbl_1_bss_1E8[i]->unk000, &pos);
            dist = fn_1_13A4(&player->pos, &pos);
            if (dist < minDist) {
                minDist = dist;
                result = i;
            }
        }
    }
    return result;
}

/* fn_1_A594 com 57 */
s16 fn_1_A594(M564_PLAYER *player)
{
    s16 result = -1;
    float minDist = 9999.9f;
    int i;
    float dist;

    for (i = 0; i < 4; i++) {
        if (player->no != i && !fn_1_5E5C(i)) {
            dist = fn_1_13A4(&lbl_1_bss_100[i]->pos, &player->pos);
            if (dist < minDist && dist > 170.0f) {
                minDist = dist;
                result = i;
            }
        }
    }
    return result;
}

/* fn_1_A678 com 18 */
int fn_1_A678(M564_PLAYER *player)
{
    if (fn_1_A6C0(player) < 120.0f) {
        return 0;
    } else {
        return 1;
    }
}

/* fn_1_A6C0 com 48 */
float fn_1_A6C0(M564_PLAYER *player)
{
    float minDist = 9999.9f;
    int i;
    float dist;

    for (i = 0; i < 4; i++) {
        if (i != player->no && !fn_1_5E5C(i)) {
            dist = fn_1_13A4(&player->pos, &lbl_1_bss_100[i]->pos);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

/* fn_1_A780 com 44 */
void fn_1_A780(M564_PLAYER *player, s16 no)
{
    HuVecF dir;
    float angle;

    fn_1_13F0(&player->pos, &lbl_1_bss_100[no]->pos, &dir);
    angle = (atan2(dir.x, dir.z) / M_PI) * 180.0;
    angle += 100.0f;
    player->unk02C->actor->rotY = angle;
}

/* fn_1_A830 com 42 */
void fn_1_A830(M564_PLAYER *player, s16 no)
{
    HuVecF dir;

    fn_1_13F0(&player->pos, &lbl_1_bss_100[no]->pos, &dir);
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, &dir, 101.0f);
    PSVECAdd(&lbl_1_bss_100[no]->pos, &dir, &player->unk040);
}

/* fn_1_A8D8 com 149 */
int fn_1_A8D8(M564_PLAYER *player, int turnF)
{
    float stkTbl[4] = { 0.8f, 0.9f, 1.0f, 1.0f };
    HuVecF dir;
    float angle;
    float target;
    float dist;
    float delta;

    dist = fn_1_13F0(&player->pos, &player->unk040, &dir);
    if (dist < 10.0f) {
        return 1;
    }
    if (turnF != 0) {

        angle = player->unk02C->actor->rotY;
        target = fn_1_12D4(&player->pos, &player->unk040);
        delta = fn_1_1338(angle, target);

        if (fabs(delta) < 15.0) {
            angle += delta;
        } else if (delta < 0.0f) {
            angle -= 15.0f;
        } else {
            angle += 15.0f;
        }
        dir.x = sin(M_PI * angle / 180.0);
        dir.z = cos(M_PI * angle / 180.0);
        dir.y = 0.0f;
    } else {
        PSVECNormalize(&dir, &dir);
    }
    player->unk064 = 56.0f * dir.x * stkTbl[player->dif];
    player->unk068 = 56.0f * -dir.z * stkTbl[player->dif];
    return 0;
}

/* fn_1_AB2C com 131 */
int fn_1_AB2C(M564_PLAYER *player, M564_PLAYER *other)
{
    HuVecF end;
    HuVecF closest;
    HuVecF dir;
    float rotY;
    float dist;

    if (other->unk034 == 0) {
        return 0;
    }
    rotY = other->unk02C->actor->rotY;
    end.x = other->pos.x + 550.0 * sin(M_PI * rotY / 180.0);
    end.z = other->pos.z + 550.0 * cos(M_PI * rotY / 180.0);
    end.y = other->pos.y;
    dist = fn_1_B380(&player->pos, &other->pos, &end, &closest);
    if (dist > 150.0f || dist < 0.0f) {
        return 0;
    }
    PSVECSubtract(&player->pos, &closest, &dir);
    if (0.0f == PSVECMag(&dir)) {
        return 0;
    }
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, &dir, 150.0f);
    PSVECAdd(&player->pos, &dir, &player->unk040);
    player->unk040.y = 0.0f;
    if (PSVECMag(&player->unk040) > 425.0f) {
        PSVECScale(&dir, &dir, 10.0f);
        PSVECSubtract(&closest, &dir, &player->unk040);
    }
    return 1;
}

/* fn_1_AD38 com 181 */
int fn_1_AD38(M564_PLAYER *player)
{
    s32 rateTbl[4] = { 0, 30, 60, 100 };
    int i;

    if ((int)frandmod(100) < rateTbl[player->dif]) {
        for (i = 0; i < 4; i++) {
            if (player->no != i && !fn_1_5E5C(i)) {
                if (fn_1_AB2C(player, lbl_1_bss_100[i])) {
                    fn_1_9C00(player, 3);
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* fn_1_B00C com 180 */
int fn_1_B00C(M564_PLAYER *player)
{
    s32 rateTbl[4] = { 60, 80, 90, 100 };
    HuVecF pos;

    if ((int)frandmod(100) < rateTbl[player->dif] && fn_1_902C(&player->pos, &pos)) {
        player->unk040 = pos;
        fn_1_A8D8(player, 1);
        return 1;
    }
    return 0;
}

/* fn_1_B2DC com 41 */
int fn_1_B2DC(M564_PLAYER *player)
{
    s32 rateTbl[4] = { 45, 30, 10, 0 };

    if ((int)frandmod(100) < rateTbl[player->dif]) {
        fn_1_118C(&lbl_1_data_D8, 0.0f, 400.0f, &player->unk040);
        return 1;
    }
    return 0;
}

/* fn_1_B380 com 64 -- m523dll fn_1_D58 */
float fn_1_B380(HuVecF *a, HuVecF *b, HuVecF *c, HuVecF *d)
{
    HuVecF seg, toA, proj, closest;
    float sqMag, t;

    PSVECSubtract(c, b, &seg);
    PSVECSubtract(a, b, &toA);
    sqMag = PSVECSquareMag(&seg);
    t = PSVECDotProduct(&seg, &toA) / sqMag;
    if (t < 0.0f || t > 1.0f) {
        return -1.0f;
    }
    PSVECScale(&seg, &proj, t);
    PSVECAdd(b, &proj, d);
    PSVECSubtract(&proj, &toA, &closest);
    return PSVECMag(&closest);
}
