/*
 * m575dll com.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/com.s.
 */

#include "REL/m575dll.h"

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
/* 0x258 */ /* float lbl_1_rodata_258 = 50.0f; */
/* 0x25C */ /* float lbl_1_rodata_25C = 6.0f; */
/* 0x260 */ /* float lbl_1_rodata_260 = 6.6666665f; */
/* 0x264 */ /* float lbl_1_rodata_264 = 7.5f; */
/* 0x268 */ /* float lbl_1_rodata_268 = 20.0f; */
/* 0x26C */ /* s32 lbl_1_rodata_26C[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x278 */ /* float lbl_1_rodata_278 = 5.0f; */
/* 0x27C */ /* float lbl_1_rodata_27C = 0.0f; */
/* 0x280 */ /* float lbl_1_rodata_280 = 25.0f; */
/* 0x284 */ /* float lbl_1_rodata_284 = 1.0f; */
/* 0x288 */ /* float lbl_1_rodata_288 = 0.5f; */
/* 0x290 */ /* double lbl_1_rodata_290 = 180; */
/* 0x298 */ /* double lbl_1_rodata_298 = 3.141592653589793; */
/* 0x2A0 */ /* double lbl_1_rodata_2A0 = 360; */
/* 0x2A8 */ /* double lbl_1_rodata_2A8 = -180; */
/* 0x2B0 */ /* float lbl_1_rodata_2B0 = 0.1f; */
/* 0x2B4 */ /* float lbl_1_rodata_2B4 = 0.2f; */
/* 0x2B8 */ /* float lbl_1_rodata_2B8 = 320.0f; */
/* 0x2BC */ /* float lbl_1_rodata_2BC = 15.0f; */
/* 0x2C0 */ /* s32 lbl_1_rodata_2C0[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x2CC */ /* s32 lbl_1_rodata_2CC[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x2D8 */ /* float lbl_1_rodata_2D8 = 500.0f; */
/* 0x2DC */ /* float lbl_1_rodata_2DC = 700.0f; */
/* 0x2E0 */ /* float lbl_1_rodata_2E0 = 350.0f; */
/* 0x2E4 */ /* float lbl_1_rodata_2E4 = 150.0f; */
/* 0x2E8 */ /* s32 lbl_1_rodata_2E8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x2F4 */ /* s32 lbl_1_rodata_2F4[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x300 */ /* float lbl_1_rodata_300 = 10.0f; */
/* 0x304 */ /* float lbl_1_rodata_304 = 10000.0f; */
/* 0x308 */ /* double lbl_1_rodata_308 = 4503599627370496; */
/* 0x310 */ /* float lbl_1_rodata_310 = 100.0f; */
/* 0x314 */ /* float lbl_1_rodata_314 = 60.0f; */
/* 0x318 */ /* float lbl_1_rodata_318 = 30.0f; */
/* 0x31C */ /* float lbl_1_rodata_31C = 0.8f; */
/* 0x320 */ /* float lbl_1_rodata_320[2] = { 56.0f, 0.0f }; */

/* --- functions (reference order) --- */

#define M575_WRAP_D(a) ((a) > 180.0 ? (a) - 360.0 : ((a) <= -180.0 ? 360.0 + (a) : (a)))

/* 75 insns */
void fn_1_6630(M575_COM *com, M575_PLAYER *player)
{
    memset(com, 0, sizeof(M575_COM));
    com->unk000 = player;
    com->unk008 = GwPlayerConf[player->unk00E].type;
    com->unk010 = (GwPlayerConf[player->unk00E].dif == 3) ? 0
        : (GwPlayerConf[player->unk00E].dif == 2) ? 1
        : (GwPlayerConf[player->unk00E].dif == 1) ? 2 : 3;
    com->unk020 = *player->unk078;
    com->unk014 = com->unk020;
    com->unk00C = 0;
}

/* 12 insns */
void fn_1_675C(M575_COM *com)
{
    memset(com, 0, sizeof(M575_COM));
}

/* 278 insns */
void fn_1_678C(M575_COM *com)
{
    M575_PLAYER *player = com->unk000;
    M575_TEAM *court = player->unk000;
    M575_TEN *ten = &court->unk1A0;
    M575_PLAYER *other = (player == &court->unk008[0]) ? &court->unk008[1] : &court->unk008[0];

    com->unk03C = 0;
    com->unk040 = 0;
    com->unk044 = 0;
    com->unk048 = 0;
    if (com->unk00C == 0) {
        return;
    }
    if (com->unk006 <= 0) {
        com->unk004 = 0;
        com->unk006 = frand() % 30 + 30;
        if (player->unk094 < 50.0f && other->unk094 > 50.0f && other->unk0A0 > 120) {
            com->unk004 = 3;
            com->unk006 = frand() % 30 + 30;
        }
        else if ((com->unk010 == 0 && ten->unk020 > 6.0f)
            || (com->unk010 == 1 && ten->unk020 > 6.6666665f && frand() % 10000 < 9500)
            || (com->unk010 == 2 && ten->unk020 > 7.5f && frand() % 10000 < 8500)
            || (com->unk010 == 3 && ten->unk020 > 20.0f && frand() % 10000 < 7500)) {
            com->unk004 = 1;
            com->unk006 = frand() % 30 + 30;
        }
        else if (com->unk010 == 0
            || (com->unk010 == 1 && frand() % 10000 < 9000)
            || (com->unk010 == 2 && frand() % 10000 < 8000)
            || (com->unk010 == 3 && frand() % 10000 < 3000)) {
            if (player->unk098 && player->unk094 > 50.0f) {
                com->unk004 = 2;
                com->unk006 = frand() % 30 + 30;
            }
            else if (other->unk094 > 50.0f && other->unk0A0 > 120) {
                com->unk004 = 3;
                com->unk006 = frand() % 30 + 30;
            }
        }
    }
    switch (com->unk004) {
        case 0:
            if (fn_1_7A80(com)) {
                com->unk006 = 0;
            }
            break;
        case 1:
            if (fn_1_6BE4(com)) {
                com->unk006 = 0;
            }
            break;
        case 2:
            if (fn_1_734C(com)) {
                com->unk006 = 0;
            }
            break;
        case 3:
            if (fn_1_79A0(com)) {
                com->unk006 = 0;
            }
            break;
    }
    if (com->unk006 != 0) {
        com->unk006--;
    }
}

/* 474 insns */
s32 fn_1_6BE4(M575_COM *com)
{
    M575_PLAYER *player = com->unk000;
    M575_TEAM *court = player->unk000;
    M575_PLAYER *other = (player == &court->unk008[0]) ? &court->unk008[1] : &court->unk008[0];
    M575_WORK *game = court->unk000;
    M575_TEN *ten = &court->unk1A0;
    M575_TUBOEFF *tenSub = &ten->unk02C;
    HuVecF vec;
    HuVecF tenDir;
    HuVecF dir;
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF *src;
    float speed;
    float scale;
    float angTen;
    float angSelf;
    float ang;

    src = &up;
    dir = *src;
    tenDir.x = tenSub->unk048[1][0];
    tenDir.y = tenSub->unk048[1][1];
    tenDir.z = tenSub->unk048[1][2];
    PSVECNormalize(&tenDir, &tenDir);
    speed = ten->unk020;
    if (speed < 5.0f) {
        return 1;
    }
    vec = tenDir;
    vec.y = 0.0f;
    if (vec.x || vec.z) {
        PSVECNormalize(&vec, &vec);
    }
    scale = (speed - 5.0f) / 25.0f;
    scale = (scale > 1.0f) ? 1.0f : (scale < 0.0f) ? 0.0f : scale;
    scale = 0.5f + 0.5f * scale;
    angTen = M575_WRAP_D(HuAtan(-vec.x, -vec.z));
    vec = player->unk088;
    vec.y = 0.0f;
    if (vec.x || vec.z) {
        PSVECNormalize(&vec, &vec);
    }
    angSelf = M575_WRAP_D(HuAtan(vec.x, vec.z));
    ang = fn_1_30CC(angSelf, angTen, 0.5f);
    vec.x = HuSin(ang);
    vec.y = 0.0f;
    vec.z = HuCos(ang);
    if (other->unk0B0 == 0 && other->unk094 > player->unk094) {
        scale *= (com->unk010 == 0) ? 0.0f : (com->unk010 == 1) ? 0.1f : 0.2f;
    }
    PSVECScale(&vec, &vec, 320.0f * scale);
    com->unk014 = vec;
    if (speed > 15.0f) {
        if (game->unk008 % 10 == 0) {
            com->unk02C = 1;
        }
    }
    else if (speed > 7.5f) {
        if (game->unk008 % 30 == 0) {
            com->unk02C = 1;
        }
    }
    fn_1_8180(com);
    return 0;
}

/* 405 insns */
s32 fn_1_734C(M575_COM *com)
{
    M575_PLAYER *player = com->unk000;
    M575_TEAM *court = player->unk000;
    M575_WORK *game = court->unk000;
    M575_TEN *ten = &court->unk1A0;
    M575_TUBOEFF *tenSub = &ten->unk02C;
    HuVecF vec;
    HuVecF dir;
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF *src;
    float dist;
    float angCoin;
    float angSelf;
    float ang;

    src = &up;
    dir = *src;
    if (!player->unk098) {
        return 1;
    }
    if (player->unk098->unk014 == 0) {
        return 1;
    }
    if (ten->unk020 > 15.0f) {
        return 1;
    }
    if (player->unk098->unk008 == 0) {
        if (player->unk09C > 500.0f) {
            return 1;
        }
    }
    else if (player->unk09C > 700.0f) {
        return 1;
    }
    if ((com->unk010 == 0 || com->unk010 == 1) && player->unk094 > 350.0f) {
        HuVecF zero = { 0.0f, 0.0f, 0.0f };
        HuVecF *zsrc = &zero;
        com->unk014 = *zsrc;
        return 1;
    }
    vec = player->unk098->unk048;
    vec.y = 0.0f;
    dist = PSVECMag(&vec);
    if (vec.x || vec.z) {
        PSVECNormalize(&vec, &vec);
    }
    angCoin = M575_WRAP_D(HuAtan(vec.x, vec.z));
    vec = player->unk088;
    vec.y = 0.0f;
    if (vec.x || vec.z) {
        PSVECNormalize(&vec, &vec);
    }
    angSelf = M575_WRAP_D(HuAtan(vec.x, vec.z));
    ang = fn_1_30CC(angSelf, angCoin, 0.5f);
    vec.x = HuSin(ang);
    vec.y = 0.0f;
    vec.z = HuCos(ang);
    dist = (dist < 150.0f) ? 150.0f : dist;
    PSVECScale(&vec, &vec, dist);
    com->unk014 = vec;
    fn_1_8180(com);
    return 0;
}

/* 56 insns */
s32 fn_1_79A0(M575_COM *com)
{
    M575_PLAYER *player = com->unk000;
    M575_TEAM *court = player->unk000;
    M575_TEN *ten = &court->unk1A0;
    M575_TUBO *tubo = &court->unkE90;

    if (player->unk094 > 50.0f && player->unk008->mode != 1) {
        HuVecF zero = { 0.0f, 0.0f, 0.0f };
        HuVecF *zsrc = &zero;
        com->unk014 = *zsrc;
        fn_1_8180(com);
        return 1;
    }
    if (tubo->unk004 == 0) {
        com->unk03C |= 0x100;
        com->unk048 |= 0x100;
    }
    return 0;
}

/* 448 insns */
s32 fn_1_7A80(M575_COM *com)
{
    M575_PLAYER *player = com->unk000;
    M575_TEAM *court = player->unk000;
    M575_WORK *game = court->unk000;
    M575_TEN *ten = &court->unk1A0;
    M575_TUBOEFF *tenSub = &ten->unk02C;
    HuVecF vec;
    HuVecF pos;
    HuVecF dir;
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF *src;
    float dist;
    float scale;
    float ang;
    float angSelf;
    float angDir;

    src = &up;
    dir = *src;
    pos = player->unk088;
    PSVECSubtract(&com->unk020, &pos, &vec);
    vec.y = 0.0f;
    dist = PSVECMag(&vec);
    if (dist < 10.0f) {
        ang = frand() % 360;
        vec.x = HuSin(ang);
        vec.y = 0.0f;
        vec.z = HuCos(ang);
        scale = (frand() % 10000) / 10000.0f;
        scale = (scale > 1.0f) ? 1.0f : (scale < 0.5f) ? 0.5f : scale;
        PSVECScale(&vec, &vec, 320.0f * scale);
        com->unk020 = vec;
    }
    vec = com->unk020;
    if (vec.x || vec.z) {
        PSVECNormalize(&vec, &vec);
    }
    ang = M575_WRAP_D(HuAtan(vec.x, vec.z));
    vec = player->unk088;
    vec.y = 0.0f;
    if (vec.x || vec.z) {
        PSVECNormalize(&vec, &vec);
    }
    angSelf = M575_WRAP_D(HuAtan(vec.x, vec.z));
    angDir = fn_1_30CC(angSelf, ang, 0.5f);
    vec.x = HuSin(angDir);
    vec.y = 0.0f;
    vec.z = HuCos(angDir);
    dist = PSVECMag(&com->unk020);
    PSVECScale(&vec, &vec, dist);
    com->unk014 = vec;
    fn_1_8180(com);
    return 0;
}

/* 231 insns */
s32 fn_1_8180(M575_COM *com)
{
    M575_PLAYER *player = com->unk000;
    M575_TEAM *court = player->unk000;
    M575_PLAYER *other = (player == &court->unk008[0]) ? &court->unk008[1] : &court->unk008[0];
    HuVecF vec;
    HuVecF diff;
    HuVecF pos;
    float dist;
    float scale;
    float mateDist;

    pos = player->unk088;
    PSVECSubtract(&com->unk014, &pos, &vec);
    vec.y = 0.0f;
    dist = PSVECMag(&vec);
    if (dist < 10.0f) {
        return 1;
    }
    PSVECSubtract(player->unk078, other->unk078, &diff);
    diff.y = 0.0f;
    mateDist = PSVECMag(&diff);
    if (dist < 100.0f && mateDist < 100.0f) {
        return 1;
    }
    if (com->unk030 != 0) {
        if (player->unk008->mode != 1) {
            com->unk030 = 0;
        }
        else if (dist > 60.0f) {
            com->unk048 |= 0x100;
        }
    }
    else if (com->unk02C != 0) {
        if (player->unk008->mode == 1) {
            com->unk02C = 0;
            com->unk030 = 1;
        }
        else if (dist > 60.0f) {
            com->unk03C |= 0x100;
            com->unk048 |= 0x100;
        }
        else {
            com->unk02C = 0;
        }
    }
    if (vec.x || vec.y || vec.z) {
        PSVECNormalize(&vec, &vec);
    }
    scale = dist / 30.0f;
    scale = (scale > 1.0f) ? 1.0f : (scale < 0.0f) ? 0.0f : scale;
    vec.x *= scale;
    vec.z *= scale;
    com->unk034 = 0.8f * com->unk034 + 0.2f * vec.x;
    com->unk038 = 0.8f * com->unk038 + 0.2f * vec.z;
    com->unk040 = (s8)(56.0f * com->unk034);
    com->unk044 = (s8)(56.0f * -com->unk038);
    return 0;
}
