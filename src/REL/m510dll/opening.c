/*
 * m510dll opening.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/opening.s.
 */

#include "REL/m510dll.h"

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
/* 0x2D8 */ /* float lbl_1_rodata_2D8 = 0.1f; */
/* 0x2DC */ /* float lbl_1_rodata_2DC = 90.0f; */
/* 0x2E0 */ /* float lbl_1_rodata_2E0 = 30.0f; */
/* 0x2E4 */ /* float lbl_1_rodata_2E4 = 0.4f; */
/* 0x2E8 */ /* double lbl_1_rodata_2E8 = 4503601774854144; */

/* --- .data --- */
/* 0x420 */ HuVecF lbl_1_data_420 = { 0.0f, 3000.0f, 16000.0f };  /* opening camera start (y, z; x from player 3's model) */
/* 0x42C */ HuVecF lbl_1_data_42C = { 0.0f, -52.0f, 400.0f };     /* opening camera start, second vector */
/* 0x438 */ HuVecF lbl_1_data_438 = { 0.0f, 0.0f, 0.0f };         /* saved camera unk00C */
/* 0x444 */ HuVecF lbl_1_data_444 = { 0.0f, 0.0f, 0.0f };         /* saved camera unk024 */

/* --- functions (reference order) --- */
/* opening.c fn_1_966C, 296 insns. Opening camera sweep and BGM; returns 1 when finished. */
s32 fn_1_966C(M510_WORK *work)
{
    float t;
    M510_CAMERA *camera;
    M510_PLAYER *p0;
    M510_PLAYER *p1;
    M510_PLAYER *p2;
    M510_PLAYER *p3;
    M510_PLAYERMODEL *pm3;
    s32 i;
    M510_PLAYERMODEL *pm0;
    M510_PLAYERMODEL *pm1;
    M510_PLAYERMODEL *pm2;
    s32 result;
    M510_PITCH *pitch;

    camera = &work->unk2474;
    p0 = &work->unk01C[0];
    p1 = &work->unk01C[1];
    p2 = &work->unk01C[2];
    p3 = &work->unk01C[3];
    pm0 = &p0->unk008;
    pm1 = &p1->unk008;
    pm2 = &p2->unk008;
    pm3 = &p3->unk008;
    result = 0;
    switch (work->unk00E) {
    case 0:
        lbl_1_data_438 = camera->unk00C;
        lbl_1_data_444 = camera->unk024;
        camera->unk00C.x = camera->unk018.x = pm3->unk0B8.x;
        camera->unk00C.y = camera->unk018.y = lbl_1_data_420.y;
        camera->unk00C.z = camera->unk018.z = lbl_1_data_420.z;
        camera->unk024.x = camera->unk030.x = pm3->unk0B8.x;
        camera->unk024.y = camera->unk030.y = lbl_1_data_42C.y;
        camera->unk024.z = camera->unk030.z = lbl_1_data_42C.z;
        camera->unk060 = 0.1f;
        work->unk014 = 0;
        work->unk018 = 0;
        work->unk00E++;
    case 1:
        if (work->unk2538 < 0) {
            work->unk2538 = fn_1_734(0x4E);
        }
        t = work->unk014 / 90.0f;
        camera->unk00C.x = camera->unk024.x = pm3->unk0B8.x + t * (lbl_1_data_438.x - pm3->unk0B8.x);
        if (work->unk014++ > 90) {
            work->unk014 = 0;
            work->unk00E++;
        }
        break;
    case 2:
        t = work->unk014 / 30.0f;
        camera->unk00C.x = camera->unk00C.x + t * (lbl_1_data_438.x - camera->unk00C.x);
        camera->unk00C.y = camera->unk00C.y + t * (lbl_1_data_438.y - camera->unk00C.y);
        camera->unk00C.z = camera->unk00C.z + t * (lbl_1_data_438.z - camera->unk00C.z);
        camera->unk024.x = camera->unk024.x + t * (lbl_1_data_444.x - camera->unk024.x);
        camera->unk024.y = camera->unk024.y + t * (lbl_1_data_444.y - camera->unk024.y);
        camera->unk024.z = camera->unk024.z + t * (lbl_1_data_444.z - camera->unk024.z);
        if (work->unk014++ > 30) {
            work->unk014 = 0;
            work->unk00E++;
        }
        break;
    case 3:
        if (work->unk014++ > 5) {
            for (i = 0; i < 4; i++) {
                pitch = &work->unk01C[i].unk118;
                pitch->unk020 = 3;
                pitch->unk024 = 1;
            }
            work->unk014 = 0;
            work->unk00E++;
        }
        break;
    case 4:
        if (work->unk014++ > 100) {
            work->unk014 = 0;
            work->unk00E++;
        }
        break;
    case 5:
        camera->unk060 = 0.4f;
        work->unk00E = 0;
        result = 1;
        break;
    }
    if (work->unk00E != 0) {
        if (work->unk018 == 20) {
            pm3->unk100 = 1;
        } else if (work->unk018 == 60) {
            pm2->unk100 = 1;
        } else if (work->unk018 == 100) {
            pm1->unk100 = 1;
        } else if (work->unk018 == 140) {
            pm0->unk100 = 1;
        } else if (work->unk018 == 184) {
            pm0->unk100 = 1;
            pm1->unk100 = 1;
            pm2->unk100 = 1;
            pm3->unk100 = 1;
        }
        work->unk018++;
    }
    return result;
}
