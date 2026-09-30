/*
 * m575dll coin.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/coin.s.
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
#include "string.h"
#include "game/charman.h"
#include "game/mg/colman.h"

/* retail passes the camera word unnarrowed (lwz, no extsh): no prototype in scope */
void Hu3D3Dto2D();

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x510 */ /* float lbl_1_rodata_510 = 0.0f; */
/* 0x514 */ /* float lbl_1_rodata_514 = 1000000.0f; */
/* 0x518 */ /* float lbl_1_rodata_518 = -0.8f; */
/* 0x51C */ /* float lbl_1_rodata_51C = -3000.0f; */
/* 0x520 */ /* float lbl_1_rodata_520 = 1.0f; */
/* 0x524 */ /* float lbl_1_rodata_524 = 0.2f; */
/* 0x528 */ /* float lbl_1_rodata_528 = 0.8f; */
/* 0x52C */ /* float lbl_1_rodata_52C = 30.0f; */
/* 0x530 */ /* float lbl_1_rodata_530 = 360.0f; */
/* 0x538 */ /* double lbl_1_rodata_538 = 4503601774854144; */
/* 0x540 */ /* float lbl_1_rodata_540 = 1.33f; */
/* 0x544 */ /* s32 lbl_1_rodata_544[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x550 */ /* s32 lbl_1_rodata_550[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x55C */ /* float lbl_1_rodata_55C = -1.0f; */
/* 0x560 */ /* float lbl_1_rodata_560 = 115.0f; */
/* 0x564 */ /* float lbl_1_rodata_564 = 450.0f; */
/* 0x568 */ /* float lbl_1_rodata_568 = -115.0f; */
/* 0x56C */ /* float lbl_1_rodata_56C = -16.0f; */
/* 0x570 */ /* float lbl_1_rodata_570 = 2.0f; */
/* 0x574 */ /* float lbl_1_rodata_574 = 576.0f; */
/* 0x578 */ /* float lbl_1_rodata_578 = 0.5f; */
/* 0x57C */ /* float lbl_1_rodata_57C = 48.0f; */
/* 0x580 */ /* float lbl_1_rodata_580 = 16.0f; */
/* 0x584 */ /* float lbl_1_rodata_584 = 80.0f; */
/* 0x588 */ /* float lbl_1_rodata_588 = 0.017453292f; */
/* 0x58C */ /* float lbl_1_rodata_58C = 0.25f; */
/* 0x590 */ /* float lbl_1_rodata_590 = -0.7f; */
/* 0x594 */ /* float lbl_1_rodata_594 = 8.0f; */
/* 0x598 */ /* float lbl_1_rodata_598 = -8.0f; */
/* 0x59C */ /* float lbl_1_rodata_59C = 50.0f; */
/* 0x5A0 */ /* float lbl_1_rodata_5A0[2] = { 100.0f, 0.0f }; */

/* --- functions (reference order) --- */
/* 97 insns */
void fn_1_AEF0(M575_COINMGR *mgr, M575_TEAM *work)
{
    s16 model;
    int i;
    memset(mgr, 0, sizeof(M575_COINMGR));
    mgr->unk000 = work;
    mgr->unk2A4 = model = Hu3DModelCreate(HuDataSelHeapReadNum(0x82000A, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    mgr->unk2A6 = model = Hu3DModelCreate(HuDataSelHeapReadNum(0x82000B, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 8; i++) {
        fn_1_B2E0(&mgr->unk004[i], mgr);
    }
}

/* 29 insns */
void fn_1_B074(M575_COINMGR *mgr)
{
    int i;
    for (i = 0; i < 8; i++) {
        fn_1_B324(&mgr->unk004[i]);
    }
    Hu3DModelKill(mgr->unk2A6);
    Hu3DModelKill(mgr->unk2A4);
    memset(mgr, 0, sizeof(M575_COINMGR));
}

/* 86 insns */
void fn_1_B0E8(M575_COINMGR *mgr)
{
    M575_TEAM *work;
    M575_COIN *coin;
    M575_PLAYER *player0;
    M575_PLAYER *player1;
    int i;
    float dist;
    Vec diff;

    work = mgr->unk000;
    player0 = &work->unk008[0];
    player1 = &work->unk008[1];
    player0->unk098 = NULL;
    player0->unk09C = 1000000.0f;
    player1->unk098 = NULL;
    player1->unk09C = 1000000.0f;
    for (i = 0; i < 8; i++) {
        coin = &mgr->unk004[i];
        if (fn_1_B354(coin)) {
            fn_1_BB6C(coin);
        }
        if (coin->unk014) {
            PSVECSubtract(player0->unk078, coin->unk00C, &diff);
            diff.y = 0.0f;
            dist = PSVECMag(&diff);
            if (dist < player0->unk09C || coin->unk008 == 1) {
                player0->unk098 = coin;
                player0->unk09C = dist;
            }
            PSVECSubtract(player1->unk078, coin->unk00C, &diff);
            diff.y = 0.0f;
            dist = PSVECMag(&diff);
            if (dist < player1->unk09C || coin->unk008 == 1) {
                player1->unk098 = coin;
                player1->unk09C = dist;
            }
        }
    }
}

/* 40 insns */
M575_COIN *fn_1_B240(M575_COINMGR *mgr, u16 kind, Vec *pos, Vec *target, float height)
{
    M575_COIN *coin;
    int i;
    coin = NULL;
    for (i = 0; i < 8; i++) {
        if (mgr->unk004[i].unk014 == 0) {
            coin = &mgr->unk004[i];
            fn_1_B91C(coin, kind, pos, target, height);
            break;
        }
    }
    return coin;
}

/* 17 insns */
void fn_1_B2E0(M575_COIN *coin, M575_COINMGR *mgr)
{
    memset(coin, 0, sizeof(M575_COIN));
    coin->unk000 = mgr;
}

/* 12 insns; donated: m565dll com.c fn_1_9FF4 */
void fn_1_B324(M575_COIN *coin)
{
    memset(coin, 0, sizeof(M575_COIN));
}

#define M575_ABS(x) (((x) >= 0.0f) ? (x) : -(x))
#define M575_CLAMP01(x) (((x) > 1.0f) ? 1.0f : (((x) < 0.0f) ? 0.0f : (x)))

/* 370 insns */
s32 fn_1_B354(M575_COIN *coin)
{
    M575_COINMGR *mgr;
    M575_TEAM *work;
    M575_TEN *ten;
    M575_WORK *seq;
    float t;
    float angle;
    Vec pos;

    mgr = coin->unk000;
    work = mgr->unk000;
    ten = &work->unk1A0;
    seq = work->unk000;
    if (coin->unk014 == 0) {
        return 0;
    }
    if (seq->unk00C >= 5) {
        if (coin->unk006 & 1) {
            Hu3DModelAttrReset(coin->unk00A, HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrSet(coin->unk00A, HU3D_ATTR_DISPOFF);
        }
        if (coin->unk006++ > 60) {
            return 1;
        }
        return 0;
    }
    coin->unk018.y += -0.8f;
    if (coin->unk00C->y < -3000.0f) {
        return 1;
    }
    if (coin->unk044 == 0) {
        pos = *coin->unk00C;
        if (coin->unk018.y > 0.0f) {
            t = M575_ABS(coin->unk018.y) / M575_ABS(coin->unk03C);
            t = 1.0f - M575_CLAMP01(t);
            pos.x = coin->unk030 + t * (0.2f * (coin->unk024 - coin->unk030));
            pos.z = coin->unk038 + t * (0.2f * (coin->unk02C - coin->unk038));
            coin->unk040 = coin->unk00C->y;
        }
        else {
            if (coin->unk00C->y < 0.0f) {
                t = 1.0f;
            }
            else {
                t = M575_ABS(coin->unk00C->y) / M575_ABS(coin->unk040);
                t = 1.0f - M575_CLAMP01(t);
            }
            pos.x = coin->unk030 + (0.2f + 0.8f * t) * (coin->unk024 - coin->unk030);
            pos.z = coin->unk038 + (0.2f + 0.8f * t) * (coin->unk02C - coin->unk038);
        }
        pos.y = coin->unk00C->y + coin->unk018.y;
        PSVECSubtract(&pos, coin->unk00C, &coin->unk018);
        *coin->unk00C = pos;
    }
    else {
        PSVECAdd(coin->unk00C, &coin->unk018, coin->unk00C);
    }
    if (coin->unk008 == 0) {
        angle = (seq->unk008 % 30) / 30.0f;
        angle *= 360.0f;
        Hu3DModelRotSet(coin->unk00A, 0.0f, angle, 0.0f);
    }
    else {
        Hu3DModelRotSet(coin->unk00A, 0.0f, 0.0f, 0.0f);
    }
    fn_1_BC18(coin, ten);
    if (fn_1_C184(coin, &work->unk008[0])) {
        return 1;
    }
    if (fn_1_C184(coin, &work->unk008[1])) {
        return 1;
    }
    return 0;
}

/* 148 insns */
void fn_1_B91C(M575_COIN *coin, u16 kind, Vec *pos, Vec *target, float height)
{
    M575_COINMGR *mgr;
    M575_TEAM *work;
    M575_CAMERA *camera;
    s16 model;

    mgr = coin->unk000;
    work = mgr->unk000;
    camera = &work->unkE20;
    if (coin->unk014 == 0 && ColMapInitCheck()) {
        coin->unk008 = kind;
        coin->unk03C = height;
        model = 0;
        if (kind == 1) {
            coin->unk00A = model = Hu3DModelLink(mgr->unk2A6);
            Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
        }
        else {
            coin->unk00A = model = Hu3DModelLink(mgr->unk2A4);
            Hu3DModelScaleSet(model, 1.33f, 1.33f, 1.33f);
        }
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(model, camera->unk004);
        Hu3DModelLayerSet(model, 4);
        Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
        Hu3DModelShadowSet(model);
        coin->unk00C = &Hu3DData[model].pos;
        coin->unk010 = &Hu3DData[model].mtx;
        coin->unk00C->x = pos->x;
        coin->unk00C->y = pos->y;
        coin->unk00C->z = pos->z;
        coin->unk030 = pos->x;
        coin->unk034 = pos->y;
        coin->unk038 = pos->z;
        coin->unk018.x = 0.0f;
        coin->unk018.y = height;
        coin->unk018.z = 0.0f;
        coin->unk024 = target->x;
        coin->unk028 = 0.0f;
        coin->unk02C = target->z;
        coin->unk004 = 0;
        coin->unk006 = 0;
        coin->unk044 = 0;
        coin->unk014 = 1;
    }
}

/* 43 insns */
void fn_1_BB6C(M575_COIN *coin)
{
    Hu3DModelKill(coin->unk00A);
    coin->unk004 = 0;
    coin->unk006 = 0;
    coin->unk008 = 0;
    coin->unk00A = 0;
    coin->unk00C = NULL;
    coin->unk010 = NULL;
    {
        Vec zero = { 0.0f, 0.0f, 0.0f };
        Vec *src = &zero;
        coin->unk018 = *src;
    }
    coin->unk014 = 0;
}

/* 347 insns */
void fn_1_BC18(M575_COIN *coin, M575_TEN *ten)
{
    M575_TEAM *work;
    M575_TUBOEFF *eff;
    int seId;
    int seNo;
    float dist;
    float pan;
    float dot;
    Mtx inv;
    Mtx rot;
    Vec local;
    Vec dir;
    Vec up;
    Vec axis;
    Vec screen;
    Vec base;

    work = ten->unk000;
    eff = &ten->unk02C;
    up.x = eff->unk048[1][0];
    up.y = eff->unk048[1][1];
    up.z = eff->unk048[1][2];
    local = *coin->unk00C;
    PSMTXCopy(eff->unk078, inv);
    PSMTXMultVec(inv, &local, &local);
    local.x *= -1.0f;
    local.z *= -1.0f;
    PSVECSubtract(&local, ten->unk008, &local);
    coin->unk048 = local;
    dir = local;
    dir.y = 0.0f;
    dist = PSVECMag(&dir);
    if (local.y < 115.0f && dist < 450.0f && local.y > -115.0f) {
        if (coin->unk018.y < -16.0f) {
            Hu3D3Dto2D(coin->unk00C, work->unkE20.unk004, &screen);
            pan = 2.0f * (screen.x / 576.0f - 0.5f);
            pan = (work->unk004 == 0) ? 48.0f + 16.0f * pan : 80.0f + 16.0f * pan;
            if (coin->unk008 == 1) {
                seId = 0x14;
            }
            else {
                seId = 0x12;
            }
            seNo = fn_1_530(seId);
            fn_1_5B0(seNo, pan);
        }
        dist = 115.0f - local.y;
        PSVECNormalize(&up, &dir);
        PSVECScale(&dir, &dir, dist);
        PSVECAdd(coin->unk00C, &dir, coin->unk00C);
        {
            Vec yAxis = { 0.0f, 1.0f, 0.0f };
            Vec *src = &yAxis;
            base = *src;
        }
        dir.x = up.x;
        dir.y = 0.0f;
        dir.z = up.z;
        if (dir.x || dir.z) {
            PSVECNormalize(&dir, &dir);
            PSVECCrossProduct(&base, &dir, &axis);
            PSMTXRotAxisRad(rot, &axis, 0.017453292f * (0.25f * ten->unk020));
            PSMTXMultVec(rot, &base, &up);
        }
        dot = PSVECDotProduct(&up, &coin->unk018);
        dir.x = 2.0f * dot * up.x;
        dir.y = 2.0f * dot * up.y;
        dir.z = 2.0f * dot * up.z;
        PSVECSubtract(&dir, &coin->unk018, &dir);
        dir.y *= -0.7f;
        if (M575_ABS(dir.y) < 8.0f) {
            dir.y = (dir.y < 0.0f) ? -8.0f : 8.0f;
        }
        coin->unk018.y = dir.y;
        dir.y = 0.0f;
        PSVECScale(&dir, &dir, -0.7f);
        dist = PSVECMag(&dir);
        if (dist < 2.0f) {
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, 2.0f);
        }
        coin->unk018.x = dir.x;
        coin->unk018.z = dir.z;
        coin->unk044 = 1;
        PSVECAdd(coin->unk00C, &coin->unk018, coin->unk00C);
    }
}

/* 184 insns */
s32 fn_1_C184(M575_COIN *coin, M575_PLAYER *player)
{
    M575_TEAM *work;
    M575_WORK *seq;
    M575_SCORE *score;
    M575_CAMERA *camera;
    s32 ret;
    int seId;
    int seNo;
    float bottom;
    float top;
    float lo;
    float hi;
    float dist;
    float pan;
    Vec diff;
    Vec screen;

    work = player->unk000;
    seq = work->unk000;
    score = &work->unk1284;
    camera = &work->unkE20;
    bottom = player->unk078->y;
    top = player->unk078->y + player->unk028;
    lo = coin->unk00C->y - 50.0f;
    hi = 50.0f + coin->unk00C->y;
    if (seq->unk00C >= 5) {
        return 0;
    }
    ret = 0;
    if ((bottom >= lo && top < hi) || (bottom <= lo && top > hi) || (top >= lo && top < hi)) {
        diff.x = player->unk078->x - coin->unk00C->x;
        diff.y = 0.0f;
        diff.z = player->unk078->z - coin->unk00C->z;
        dist = PSVECMag(&diff);
        if (player->unk0B0 == 0 && dist < 100.0f) {
            CharEffectCoinGlowCreate(camera->unk004, coin->unk00C);
            if (coin->unk008 == 1) {
                score->unk010 += 5;
            }
            else {
                score->unk010 += 1;
            }
            Hu3D3Dto2D(coin->unk00C, work->unkE20.unk004, &screen);
            pan = 2.0f * (screen.x / 576.0f - 0.5f);
            pan = (work->unk004 == 0) ? 48.0f + 16.0f * pan : 80.0f + 16.0f * pan;
            if (coin->unk008 == 1) {
                seId = 0x13;
            }
            else {
                seId = 7;
            }
            seNo = fn_1_530(seId);
            fn_1_5B0(seNo, pan);
            omVibrate(player->unk00E, 15, 6, 6);
            ret = 1;
        }
    }
    return ret;
}
