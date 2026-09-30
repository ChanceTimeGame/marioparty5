/*
 * m565dll opening.c -- written 2026-09-23 (W1 forks; see NOTES.md). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m565dll/asm/REL/m565dll/opening.s.
 */

#include "REL/m565dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"
#include "game/wipe.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x358 */ /* float lbl_1_rodata_358 = 0.0f; */
/* 0x35C */ /* float lbl_1_rodata_35C = 72.0f; */
/* 0x360 */ /* float lbl_1_rodata_360 = 0.6f; */
/* 0x364 */ /* float lbl_1_rodata_364 = 144.0f; */
/* 0x368 */ /* float lbl_1_rodata_368 = 216.0f; */
/* 0x36C */ /* float lbl_1_rodata_36C = 288.0f; */
/* 0x370 */ /* float lbl_1_rodata_370 = 360.0f; */
/* 0x374 */ /* float lbl_1_rodata_374 = 25.0f; */
/* 0x378 */ /* float lbl_1_rodata_378 = 0.95f; */
/* 0x37C */ /* float lbl_1_rodata_37C = 90.0f; */
/* 0x380 */ /* float lbl_1_rodata_380 = 4.0f; */
/* 0x388 */ /* double lbl_1_rodata_388 = 3.141592653589793; */
/* 0x390 */ /* double lbl_1_rodata_390 = 180; */
/* 0x398 */ /* float lbl_1_rodata_398 = 180.0f; */
/* 0x39C */ /* float lbl_1_rodata_39C = -180.0f; */
/* 0x3A0 */ /* float lbl_1_rodata_3A0 = 3.0f; */
/* 0x3A4 */ /* float lbl_1_rodata_3A4 = 0.9f; */

/* --- .data --- */
/* 0xBE0 */ /* jumptable_1_data_BE0: the switch in fn_1_E740 (9 cases) */

/* --- functions (reference order) --- */
#define M565_ANGLE_WRAP(a) ((a) > 180.0f ? (a) - 360.0f : ((a) <= -180.0f ? 360.0f + (a) : (a)))

/* 451 insns. Opening sequence, stepped by work->unk00E; returns 1 when done. */
s32 fn_1_E740(M565_WORK *work)
{
    HuVecF dir;
    HuVecF to;
    float dot;
    float ang;
    float maxTime;
    float diff;
    float target;
    M565_PLAYER *player;
    s32 i;
    M565_PUKU2OBJ *puku;
    s16 count;
    M565_OBJECT *obj;
    s32 result;

    obj = &work->unk018;
    result = 0;
    switch (work->unk00E) {
    case 0:
        for (i = 0; i < 4; i++) {
            player = &obj->unk008[i];
            fn_1_8984(player, 0);
            Hu3DModelRotSet(player->unk010, 0.0f, 0.0f, 0.0f);
            Hu3DModelPosSet(player->unk010, player->unk074->x, 0.0f, player->unk074->z);
            Hu3DMotionSet(player->unk010, player->unk012[0]);
            Hu3DModelAttrSet(player->unk010, HU3D_MOTATTR_LOOP);
        }
        work->unk00E++;
        break;
    case 1:
        if (!WipeCheckEnd()) {
            work->unk00E++;
        }
        break;
    case 2:
        puku = fn_1_3284(obj, 72.0f, 0.6f, 1);
        if (puku) {
            puku->unk030 = 10;
        }
        puku = fn_1_3284(obj, 144.0f, 0.6f, 1);
        if (puku) {
            puku->unk030 = 10;
        }
        puku = fn_1_3284(obj, 216.0f, 0.6f, 1);
        if (puku) {
            puku->unk030 = 10;
        }
        puku = fn_1_3284(obj, 288.0f, 0.6f, 1);
        if (puku) {
            puku->unk030 = 10;
        }
        puku = fn_1_3284(obj, 360.0f, 0.6f, 1);
        if (puku) {
            puku->unk030 = 10;
        }
        fn_1_C18(0x8DE);
        work->unk00E++;
        break;
    case 3:
        if (work->unk018.unk3824 == 0) {
            fn_1_C18(0x8DF);
            omVibrate(0, 30, 12, 0);
            omVibrate(1, 30, 12, 0);
            omVibrate(2, 30, 12, 0);
            omVibrate(3, 30, 12, 0);
            for (i = 0; i < 4; i++) {
                player = &obj->unk008[i];
                Hu3DMotionSet(player->unk010, player->unk012[3]);
                Hu3DModelAttrReset(player->unk010, HU3D_MOTATTR_LOOP);
            }
            fn_1_366C(obj, 60, 25.0f, 0.95f, 90.0f);
            work->unk00E++;
        }
        break;
    case 4:
        player = &obj->unk008[0];
        maxTime = Hu3DMotionMaxTimeGet(player->unk010);
        if (!(Hu3DMotionTimeGet(player->unk010) < maxTime)) {
            work->unk014 = 0;
            work->unk00E++;
        }
        break;
    case 5:
        if (work->unk014++ >= 60) {
            for (i = 0; i < 4; i++) {
                player = &obj->unk008[i];
                Hu3DMotionShiftSet(player->unk010, player->unk012[1], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            }
            work->unk00E++;
        }
        break;
    case 6:
        count = 0;
        for (i = 0; i < 4; i++) {
            player = &obj->unk008[i];
            dir.x = sin(M_PI * player->unk07C / 180.0);
            dir.y = 0.0f;
            dir.z = cos(M_PI * player->unk07C / 180.0);
            to.x = -player->unk074->x;
            to.y = 0.0f;
            to.z = -player->unk074->z;
            PSVECNormalize(&to, &to);
            dot = PSVECDotProduct(&dir, &to);
            ang = acos(dot);
            diff = 180.0 * (ang / M_PI);
            target = 180.0 * (atan2(to.x, to.z) / M_PI);
            target = M565_ANGLE_WRAP(target);
            if ((diff >= 0.0f ? diff : -diff) > 3.0f) {
                player->unk07C = fn_1_8F4(target, player->unk07C, 0.9f);
            } else {
                Hu3DMotionShiftSet(player->unk010, player->unk012[0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
                player->unk004->actor->rotY = target;
                player->unk07C = target;
                count++;
            }
            Hu3DModelRotSet(player->unk010, 0.0f, player->unk07C, 0.0f);
        }
        if (count >= 4) {
            work->unk00E++;
        }
        break;
    case 7:
        if (work->unk018.unk3648.unk1D0 == 0 && work->unk018.unk3828 == 0) {
            work->unk00E++;
        }
        break;
    case 8:
        work->unk00E = 0;
        result = 1;
        break;
    }
    return result;
}
