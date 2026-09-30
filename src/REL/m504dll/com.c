/*
 * m504dll com.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m504dll/asm/REL/m504dll/com.s.
 */

#include "REL/m504dll.h"

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
/* 0x2E8 */ /* s32 lbl_1_rodata_2E8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x2F4 */ /* float lbl_1_rodata_2F4 = 0.0f; */
/* 0x2F8 */ /* float lbl_1_rodata_2F8 = 15.0f; */
/* 0x2FC */ /* float lbl_1_rodata_2FC = 1.0f; */
/* 0x300 */ /* float lbl_1_rodata_300 = 0.2f; */
/* 0x304 */ /* float lbl_1_rodata_304 = 0.8f; */
/* 0x308 */ /* float lbl_1_rodata_308 = 56.0f; */
/* 0x30C */ /* float lbl_1_rodata_30C = 600.0f; */
/* 0x310 */ /* float lbl_1_rodata_310[2] = { 700.0f, 0.0f }; */

/* --- .data --- */
/* 0x45C0: jumptable_1_data_45C0 is fn_1_BC84's switch (cases 0..7) */

/* --- functions (reference order) --- */
/* 12 insns */
void fn_1_BC54(M504_COM *com)
{
    memset(com, 0, sizeof(M504_COM));
}

/* 155 insns */
void fn_1_BC84(M504_COM *com)
{
    M504_INPUT *input = com->unk000;
    M504_PLAYER *player = input->unk000;
    M504_LANE *lane = player->unk000;
    M504_WANWAN *wanwan = &lane->unk0DC;
    M504_NODE *node;
    M504_PATH *path0;
    M504_PATH *path1;

    input->unk030 = 0;
    input->unk034 = input->unk035 = 0;
    node = com->unk008;
    if (node) {
        path0 = node->unk00;
        path1 = node->unk04;
        if (path0->num == 0) {
            com->unk004 = 6;
        }
        else if (path0->num < 0) {
            com->unk004 = 7;
        }
        switch (com->unk004) {
            case 0:
                if (fn_1_BEF0(com, path0)) {
                    com->unk004 = 1;
                    com->unk006 = 0;
                    com->unk00C = fn_1_C3E0(com);
                }
                break;
            case 1:
                if (com->unk00C != 0) {
                    com->unk00C--;
                }
                else if (com->unk014 == 0 || com->unk014 == 1) {
                    if (wanwan->unk004 == 5 || wanwan->unk004 == 6) {
                        com->unk004 = 2;
                        com->unk00C = 0;
                    }
                }
                else if (wanwan->unk004 == 6) {
                    com->unk004 = 2;
                    com->unk00C = 0;
                }
                break;
            case 2:
                if (fn_1_C178(com)) {
                    com->unk004 = 3;
                }
                break;
            case 3:
                if (fn_1_C1E8(com)) {
                    com->unk004 = 4;
                }
                break;
            case 4:
                if (fn_1_BEF0(com, path1)) {
                    com->unk004 = 5;
                    com->unk006 = 0;
                    com->unk00C = fn_1_C3E0(com);
                }
                break;
            case 5:
                if (com->unk00C != 0) {
                    com->unk00C--;
                }
                else if (com->unk014 == 0 || com->unk014 == 1) {
                    if (wanwan->unk004 == 5) {
                        com->unk004 = 6;
                        com->unk00C = 0;
                    }
                }
                else if (wanwan->unk004 == 6) {
                    com->unk004 = 6;
                    com->unk00C = 0;
                }
                break;
            case 6:
                com->unk008 = fn_1_C2CC(com, node);
                com->unk004 = 0;
                break;
            case 7:
                break;
        }
    }
}

/* 162 insns */
s32 fn_1_BEF0(M504_COM *com, M504_PATH *path)
{
    M504_INPUT *input = com->unk000;
    M504_PLAYER *player = input->unk000;
    M504_LANE *lane = player->unk000;
    s32 result = 0;
    HuVecF diff;
    HuVecF dir;
    HuVecF zero = { 0.0f, 0.0f, 0.0f };
    HuVecF *target;
    HuVecF *src;
    float dist;
    float speed;

    src = &zero;
    dir = *src;
    target = &path->pos[com->unk006];
    PSVECSubtract(target, &player->unk060, &diff);
    diff.y = 0.0f;
    dist = PSVECMag(&diff);
    speed = dist / 15.0f;
    speed = (speed > 1.0f) ? 1.0f : (speed < 0.2f) ? 0.2f : speed;
    if (dist < 15.0f) {
        player->unk060 = *target;
        com->unk006++;
        if (com->unk006 >= path->num) {
            result = 1;
        }
    }
    else {
        PSVECNormalize(&diff, &dir);
        dir.x *= speed;
        dir.z *= speed;
        com->unk018.x = 0.8f * com->unk018.x + 0.2f * dir.x;
        com->unk018.z = 0.8f * com->unk018.z + 0.2f * dir.z;
        input->unk034 = 56.0f * com->unk018.x;
        input->unk035 = 56.0f * -com->unk018.z;
    }
    return result;
}

/* 28 insns */
s32 fn_1_C178(M504_COM *com)
{
    M504_INPUT *input = com->unk000;
    M504_PLAYER *player = input->unk000;
    M504_LANE *lane = player->unk000;
    M504_WANWAN *wanwan = &lane->unk0DC;
    s32 result = 0;

    if (wanwan->unk004 == 5 || wanwan->unk004 == 6) {
        input->unk030 |= 0x100;
    }
    else {
        result = 1;
    }
    return result;
}

/* 57 insns */
s32 fn_1_C1E8(M504_COM *com)
{
    M504_WANWAN *wanwan;
    M504_PLAYER *player;
    s32 result;
    M504_INPUT *input;
    M504_LANE *lane;
    HuVecF diff;
    float dist;

    input = com->unk000;
    player = input->unk000;
    lane = player->unk000;
    wanwan = &lane->unk0DC;
    result = 0;
    PSVECSubtract(&player->unk060, &wanwan->unk038, &diff);
    dist = PSVECMag(&diff);
    if (com->unk014 == 0 || com->unk014 == 1) {
        if (wanwan->unk004 == 7) {
            result = 1;
        }
    }
    else if ((wanwan->unk004 == 3 && dist < 600.0f) || (wanwan->unk004 == 4 && dist < 700.0f)) {
        result = 1;
    }
    return result;
}

/* 69 insns */
M504_NODE *fn_1_C2CC(M504_COM *com, M504_NODE *node)
{
    s32 i;
    M504_NODE *child;
    s32 count;
    M504_NODE *next;
    s32 min;
    s32 num;
    M504_INPUT *input;
    M504_PLAYER *player;
    s32 pick;
    s32 sel;
    s32 idx[8];
    M504_LANE *lane;

    input = com->unk000;
    player = input->unk000;
    lane = player->unk000;
    next = NULL;
    num = node->num;
    min = 9999;
    for (i = 0; i < num; i++) {
        child = node->child[i];
        if (child->unk0A < min) {
            min = child->unk0A;
        }
    }
    count = 0;
    for (i = 0; i < num; i++) {
        child = node->child[i];
        if (child->unk0A == min) {
            idx[count] = i;
            count++;
        }
    }
    pick = (rand8() % (count * 10)) / 10;
    sel = idx[pick];
    next = node->child[sel];
    next->unk0A++;
    return next;
}
