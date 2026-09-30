/*
 * m575dll opening.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/opening.s.
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
/* 0x630 */ /* s32 lbl_1_rodata_630[3] = { 0x00000000, 0x00000000, 0x45A28000 }; */
/* 0x63C */ /* s32 lbl_1_rodata_63C[3] = { 0x00000000, 0xC2200000, 0x45A8C000 }; */
/* 0x648 */ /* s32 lbl_1_rodata_648[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x654 */ /* float lbl_1_rodata_654 = 0.0f; */
/* 0x658 */ /* float lbl_1_rodata_658 = 4.0f; */
/* 0x65C */ /* float lbl_1_rodata_65C = 180.0f; */
/* 0x660 */ /* float lbl_1_rodata_660 = 0.5f; */
/* 0x668 */ /* double lbl_1_rodata_668 = 3.141592653589793; */
/* 0x670 */ /* float lbl_1_rodata_670 = 90.0f; */
/* 0x678 */ /* double lbl_1_rodata_678 = 180; */
/* 0x680 */ /* float lbl_1_rodata_680 = 0.016666668f; */
/* 0x684 */ /* float lbl_1_rodata_684 = 1.0f; */
/* 0x688 */ /* float lbl_1_rodata_688 = 0.4f; */
/* 0x68C */ /* float lbl_1_rodata_68C = 0.98f; */
/* 0x690 */ /* float lbl_1_rodata_690 = 0.017453292f; */
/* 0x694 */ /* float lbl_1_rodata_694 = 3.0f; */
/* 0x698 */ /* float lbl_1_rodata_698 = 0.9f; */
/* 0x69C */ /* float lbl_1_rodata_69C = 360.0f; */
/* 0x6A0 */ /* float lbl_1_rodata_6A0 = -180.0f; */
/* 0x6A4 */ /* s32 lbl_1_rodata_6A4[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x6B0 */ /* float lbl_1_rodata_6B0 = 20.0f; */
/* 0x6B4 */ /* float lbl_1_rodata_6B4 = 700.0f; */
/* 0x6B8 */ /* float lbl_1_rodata_6B8 = 150.0f; */
/* 0x6BC */ /* float lbl_1_rodata_6BC = -150.0f; */
/* 0x6C0 */ /* double lbl_1_rodata_6C0 = 300; */
/* 0x6C8 */ /* float lbl_1_rodata_6C8[2] = { -0.005f, 0.0f }; */

/* --- .data --- */
/* 0x310 */ HuVecF lbl_1_data_310[6] = { { 5e+01f, 7e+01f, -3e+02f }, { 1e+02f, 75.0f, -3e+02f }, { 2e+02f, 175.0f, -5e+02f }, { 3e+02f, 275.0f, -6e+02f }, { 1e+03f, 5e+02f, -3e+02f }, { 0.0f, 1.37e+03f, 1.27e+03f } };
/* 0x358 */ HuVecF lbl_1_data_358[6] = { { 0.0f, 7e+01f, 0.0f }, { 0.0f, 7e+01f, 0.0f }, { 0.0f, 7e+01f, 0.0f }, { 0.0f, 7e+01f, 0.0f }, { 0.0f, 1e+02f, 0.0f }, { 0.0f, 2e+02f, 0.0f } };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7B90 */ float lbl_1_bss_7B90[2]; /* [0] camera blend 0..1; [1] never referenced (dtk size 8) */
/* 0x7B84 */ HuVecF lbl_1_bss_7B84; /* saved camera eye goal */
/* 0x7B78 */ HuVecF lbl_1_bss_7B78; /* saved camera target goal */
/* 0x79B4 */ struct {
    M575_PATH unk000;
    u8 pad194[0x30]; /* never referenced; dtk sizes the symbol 0x1C4 */
} lbl_1_bss_79B4; /* eye path */
/* 0x7820 */ M575_PATH lbl_1_bss_7820; /* target path */

#define M575_ABS(x) (((x) >= 0.0f) ? (x) : -(x))
#define M575_CLAMP(x, lo, hi) (((x) > (hi)) ? (hi) : (((x) < (lo)) ? (lo) : (x)))

/* --- functions (reference order) --- */
/* 1041 insns. The opening: returns 1 when done. */
s32 fn_1_D00C(M575_WORK *work)
{
    Mtx mtx;
    HuVecF v;
    HuVecF vec;
    Quaternion q;
    Quaternion q2;
    Quaternion q3;
    HuVecF dir;
    HuVecF cross;
    HuVecF up;
    float angle;
    float t;
    M575_PLAYER *p0;
    M575_PLAYER *p1;
    M575_CAMERA *camera;
    M575_TEAM *team;
    M575_TUBOEFF *eff;
    s32 j;
    s32 i;
    M575_TEN *ten;
    M575_CAMERA *camera2;
    s32 result;
    M575_TEAM *team2;
    s32 done0;
    s32 done1;

    team = &work->unk018[0];
    team2 = &work->unk018[1];
    p0 = &team->unk008[0];
    p1 = &team->unk008[1];
    camera = &team->unkE20;
    camera2 = &team2->unkE20;
    ten = &team->unk1A0;
    eff = &ten->unk02C;
    result = 0;
    switch (work->unk00E) {
    case 0:
        fn_1_5C88(p0, 0);
        fn_1_5C88(p1, 0);
        Hu3DMotionShiftSet(p0->unk014, p0->unk016[2], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
        Hu3DMotionShiftSet(p1->unk014, p1->unk016[2], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
        *p0->unk078 = (HuVecF) { 0.0f, 0.0f, 5200.0f };
        *p1->unk078 = (HuVecF) { 0.0f, -40.0f, 5400.0f };
        Hu3DModelRotSet(p0->unk014, 0.0f, 180.0f, 0.0f);
        Hu3DModelRotSet(p1->unk014, 0.0f, 180.0f, 0.0f);
        p0->unk004 = p1->unk004 = 0;
        p0->unk006 = p1->unk006 = 0;
        lbl_1_bss_7B84 = camera->unk00C;
        lbl_1_bss_7B78 = camera->unk024;
        fn_1_31E8(&lbl_1_bss_79B4.unk000);
        fn_1_31E8(&lbl_1_bss_7820);
        fn_1_3248(&lbl_1_bss_79B4.unk000, lbl_1_data_310[0], 40);
        fn_1_3248(&lbl_1_bss_79B4.unk000, lbl_1_data_310[1], 40);
        fn_1_3248(&lbl_1_bss_79B4.unk000, lbl_1_data_310[2], 20);
        fn_1_3248(&lbl_1_bss_79B4.unk000, lbl_1_data_310[3], 60);
        fn_1_3248(&lbl_1_bss_79B4.unk000, lbl_1_data_310[4], 60);
        fn_1_3248(&lbl_1_bss_79B4.unk000, lbl_1_data_310[5], 40);
        fn_1_3248(&lbl_1_bss_7820, lbl_1_data_358[0], 40);
        fn_1_3248(&lbl_1_bss_7820, lbl_1_data_358[1], 40);
        fn_1_3248(&lbl_1_bss_7820, lbl_1_data_358[2], 20);
        fn_1_3248(&lbl_1_bss_7820, lbl_1_data_358[3], 60);
        fn_1_3248(&lbl_1_bss_7820, lbl_1_data_358[4], 60);
        fn_1_3248(&lbl_1_bss_7820, lbl_1_data_358[5], 40);
        vec = lbl_1_data_310[0];
        camera->unk00C.x = camera->unk018.x = vec.x;
        camera->unk00C.y = camera->unk018.y = p0->unk078->y + vec.y;
        camera->unk00C.z = camera->unk018.z = p0->unk078->z + vec.z;
        vec = lbl_1_data_358[0];
        vec.y = (vec.y < 0.5f * p0->unk028) ? 0.5f * p0->unk028 : vec.y;
        camera->unk024.x = camera->unk030.x = p0->unk078->x + vec.x;
        camera->unk024.y = camera->unk030.y = p0->unk078->y + vec.y;
        camera->unk024.z = camera->unk030.z = p0->unk078->z + vec.z;
        camera->unk064 = 1;
        for (i = 0; i < 30; i++) {
            fn_1_E050(work, p0);
            fn_1_E050(work, p1);
            for (j = 0; j < 60; j++) {
                fn_1_46B4(&team->unk2B8.unk020[j]);
            }
        }
        Hu3DMotionSet(team->unk2B8.unk012, team->unk2B8.unk01A);
        if (work->unk2610 < 0) {
            work->unk2610 = fn_1_530(0x92F);
        }
        work->unk014 = 0;
        work->unk00E++;
        break;
    case 1:
        done0 = fn_1_E050(work, p0);
        done1 = fn_1_E050(work, p1);
        vec = fn_1_33C4(&lbl_1_bss_79B4.unk000, work->unk014);
        camera->unk00C.x = vec.x;
        camera->unk00C.y = p0->unk078->y + vec.y;
        camera->unk00C.z = p0->unk078->z + vec.z;
        vec = fn_1_33C4(&lbl_1_bss_7820, work->unk014);
        vec.y = (vec.y < 0.5f * p0->unk028) ? 0.5f * p0->unk028 : vec.y;
        camera->unk024.x = vec.x;
        camera->unk024.y = p0->unk078->y + vec.y;
        camera->unk024.z = p0->unk078->z + vec.z;
        work->unk014++;
        if (done0 && done1) {
            lbl_1_bss_7B90[0] = 0.0f;
            Hu3DModelAttrSet(team->unk2B8.unk00E, HU3D_ATTR_DISPOFF);
            camera->unk00C = lbl_1_bss_7B84;
            camera->unk024 = lbl_1_bss_7B78;
            work->unk014 = 0;
            work->unk00E++;
        }
        break;
    case 2:
        fn_1_E050(work, p0);
        fn_1_E050(work, p1);
        if (work->unk014++ > 30) {
            p0->unk078->y = p1->unk078->y = 0.0f;
            Hu3DMotionShiftSet(p0->unk014, p0->unk016[1], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            Hu3DMotionShiftSet(p1->unk014, p1->unk016[1], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            camera->unk064 = 0;
            work->unk014 = 0;
            work->unk00E++;
        }
        break;
    case 3:
        t = HuSin(90.0f * lbl_1_bss_7B90[0]);
        t = t * t;
        fn_1_89D8(camera, camera2, 0.5f * t);
        lbl_1_bss_7B90[0] += 0.016666668f;
        if (!(lbl_1_bss_7B90[0] < 1.0f)) {
            fn_1_89D8(camera, camera2, 0.5f);
            work->unk014 = 0;
            work->unk00E++;
        }
        break;
    case 4:
        if (work->unk2610 >= 0) {
            fn_1_558(work->unk2610);
            work->unk2610 = -1;
        }
        fn_1_3218(&lbl_1_bss_7820);
        fn_1_3218(&lbl_1_bss_79B4.unk000);
        camera->unk060 = 0.4f;
        p0->unk004 = p1->unk004 = 0;
        p0->unk006 = p1->unk006 = 0;
        work->unk00E = 0;
        result = 1;
        break;
    }
    if (work->unk00E >= 2) {
        up = (HuVecF) { 0.0f, 1.0f, 0.0f };
        dir.x = eff->unk048[1][0];
        dir.y = eff->unk048[1][1];
        dir.z = eff->unk048[1][2];
        v.x = dir.x;
        v.y = 0.0f;
        v.z = dir.z;
        angle = 0.98f * (ten->unk020 - 0.5f);
        angle = M575_CLAMP(angle, 0.0f, 90.0f);
        PSVECNormalize(&v, &v);
        PSVECCrossProduct(&up, &v, &cross);
        PSMTXRotAxisRad(mtx, &cross, 0.017453292f * angle);
        PSMTXMultVec(mtx, &up, &v);
        fn_1_2D5C(&q, &dir, &v);
        C_QUATMtx(&q2, eff->unk048);
        PSQUATMultiply(&q, &q2, &q3);
        PSMTXQuat(eff->unk048, &q3);
    }
    if (work->unk00E >= 3) {
        if (M575_ABS(p0->unk07C->y) > 3.0f) {
            p0->unk07C->y = fn_1_30CC(0.0f, p0->unk07C->y, 0.9f);
            p0->unk07C->y = (p0->unk07C->y > 180.0f) ? p0->unk07C->y - 360.0f
                                                     : ((p0->unk07C->y <= -180.0f) ? 360.0f + p0->unk07C->y : p0->unk07C->y);
            if (M575_ABS(p0->unk07C->y) <= 3.0f) {
                p0->unk07C->y = 0.0f;
                Hu3DMotionShiftSet(p0->unk014, p0->unk016[0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            }
        }
        if (M575_ABS(p1->unk07C->y) > 3.0f) {
            p1->unk07C->y = fn_1_30CC(0.0f, p1->unk07C->y, 0.9f);
            p1->unk07C->y = (p1->unk07C->y > 180.0f) ? p1->unk07C->y - 360.0f
                                                     : ((p1->unk07C->y <= -180.0f) ? 360.0f + p1->unk07C->y : p1->unk07C->y);
            if (M575_ABS(p1->unk07C->y) <= 3.0f) {
                p1->unk07C->y = 0.0f;
                Hu3DMotionShiftSet(p1->unk014, p1->unk016[0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            }
        }
    }
    if (camera->unk064 && work->unk008 % 5 == 0) {
        omVibrate(0, 2, 12, 0);
        omVibrate(1, 2, 12, 0);
        omVibrate(2, 2, 12, 0);
        omVibrate(3, 2, 12, 0);
    }
    return result;
}

/* 245 insns. One player's walk-in: returns 1 when done. */
s32 fn_1_E050(M575_WORK *work, M575_PLAYER *player)
{
    HuVecF goal;
    HuVecF diff;
    HuVecF side;
    float s;
    float d;
    s32 result;
    M575_TUBOEFF *eff;
    M575_TEAM *team;
    M575_TEN *ten;

    team = player->unk000;
    ten = &team->unk1A0;
    eff = &ten->unk02C;
    result = 0;
    switch (player->unk004) {
    case 0:
        player->unk078->z -= 20.0f;
        if (player->unk078->z <= 700.0f) {
            player->unk078->z = 700.0f;
            Hu3DMotionShiftSet(player->unk014, player->unk016[3], 0.0f, 4.0f, 0);
            player->unk006 = 0;
            player->unk004++;
        }
        break;
    case 1:
        player->unk078->z -= 20.0f;
        goal = (HuVecF) { 0.0f, 0.0f, 0.0f };
        goal.x = (player->unk00C & 1) ? 150.0f : -150.0f;
        PSVECSubtract(&goal, player->unk078, &diff);
        diff.y = 0.0f;
        d = PSVECMag(&diff);
        s = 1.0f - d / 700.0f;
        player->unk078->x = goal.x * s;
        player->unk078->y = 300.0 * HuSin(180.0f * s);
        if (player->unk078->z <= 0.0f) {
            Hu3DMotionShiftSet(player->unk014, player->unk016[4], 0.0f, 4.0f, 0);
            diff.x = 0.0f;
            diff.y = -0.005f;
            diff.z = 0.0f;
            fn_1_9B58(eff, &diff, player->unk078);
            player->unk006 = 0;
            player->unk004++;
        }
        break;
    case 2:
        if (Hu3DMotionShiftIDGet(player->unk014) < 0) {
            Hu3DMotionShiftSet(player->unk014, player->unk016[0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            player->unk006 = 0;
            player->unk004++;
        }
        break;
    case 3:
        result = 1;
        break;
    }
    if (player->unk004 >= 2) {
        side.x = eff->unk048[0][0];
        side.y = eff->unk048[0][1];
        side.z = eff->unk048[0][2];
        PSVECScale(&side, &diff, 150.0f);
        player->unk078->y = (player->unk00C & 1) ? -diff.y : diff.y;
    }
    return result;
}
