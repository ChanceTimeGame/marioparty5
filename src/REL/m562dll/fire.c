/*
 * m562dll fire.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/fire.s.
 */

#include "REL/m562dll.h"

#include "game/audio.h"
#include "game/frand.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/mg/seqman.h"
#include "game/gamemes.h"
#include "game/printfunc.h"
#include "math.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#include "game/esprite.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_5E0 = 0.0f; /* 0x5E0 */
static const float lbl_1_rodata_5E4 = 10000.0f; /* 0x5E4 */
static const float lbl_1_rodata_5E8 = -625.0f; /* 0x5E8 */
static const float lbl_1_rodata_5EC = 1250.0f; /* 0x5EC */
static const float lbl_1_rodata_5F0 = -500.0f; /* 0x5F0 */
static const float lbl_1_rodata_5F4 = 1000.0f; /* 0x5F4 */
static const double lbl_1_rodata_5F8 = 0.5; /* 0x5F8 */
static const double lbl_1_rodata_600 = 3.0; /* 0x600 */
static const float lbl_1_rodata_608 = 200.0f; /* 0x608 */
/* 0x610 lbl_1_rodata_610 = 4503599627370496: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_618 = 60.0f; /* 0x618 */
static const float lbl_1_rodata_61C = 1.3f; /* 0x61C */
static const float lbl_1_rodata_620 = 0.5f; /* 0x620 */
static const float lbl_1_rodata_624 = 120.0f; /* 0x624 */
static const float lbl_1_rodata_628 = 100.0f; /* 0x628 */
static const float lbl_1_rodata_62C = 1.0f; /* 0x62C */
static const double lbl_1_rodata_630 = 180.0; /* 0x630 */
static const double lbl_1_rodata_638 = 3.141592653589793; /* 0x638 */
static const double lbl_1_rodata_640 = 360.0; /* 0x640 */
static const double lbl_1_rodata_648 = -180.0; /* 0x648 */
static const float lbl_1_rodata_650 = 110.0f; /* 0x650 */
static const float lbl_1_rodata_654 = 88.0f; /* 0x654 */
static const double lbl_1_rodata_658 = 600.0; /* 0x658 */
static const float lbl_1_rodata_660 = 2.0f; /* 0x660 */
static const float lbl_1_rodata_664 = 576.0f; /* 0x664 */
static const float lbl_1_rodata_668 = 64.0f; /* 0x668 */
static const float lbl_1_rodata_66C = 32.0f; /* 0x66C */
static const float lbl_1_rodata_670 = 30.0f; /* 0x670 */
static const float lbl_1_rodata_674 = 40.0f; /* 0x674 */
static const float lbl_1_rodata_678 = 10.0f; /* 0x678 */
static const float lbl_1_rodata_67C = 20.0f; /* 0x67C */
static const float lbl_1_rodata_680 = 96.0f; /* 0x680 */
/* 0x688 lbl_1_rodata_688 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_690 = 170.0f; /* 0x690 */
static const double lbl_1_rodata_698 = 0.5235987755982988; /* 0x698 */
static const float lbl_1_rodata_6A0 = 360.0f; /* 0x6A0 */
static const float lbl_1_rodata_6A4 = 180.0f; /* 0x6A4 */
static const float lbl_1_rodata_6A8 = -180.0f; /* 0x6A8 */
static const float lbl_1_rodata_6AC = 0.8f; /* 0x6AC */
static const float lbl_1_rodata_6B0 = 4.0f; /* 0x6B0 */
static const float lbl_1_rodata_6B4 = 1.5f; /* 0x6B4 */
static const float lbl_1_rodata_6B8 = 625.0f; /* 0x6B8 */
static const float lbl_1_rodata_6BC = 500.0f; /* 0x6BC */
static const float lbl_1_rodata_6C0 = 5.0f; /* 0x6C0 */
static const float lbl_1_rodata_6C4 = 90.0f; /* 0x6C4 */
static const float lbl_1_rodata_6C8 = -90.0f; /* 0x6C8 */
static const float lbl_1_rodata_6CC = 0.95f; /* 0x6CC */
static const double lbl_1_rodata_6D0 = 7.0; /* 0x6D0 */
static const float lbl_1_rodata_6D8 = 7.0f; /* 0x6D8 */
static const float lbl_1_rodata_6DC = 300.0f; /* 0x6DC */
static const double lbl_1_rodata_6E0 = 14.0; /* 0x6E0 */

#define M562_DATA(n) HuDataSelHeapReadNum(DATANUM(DATA_m562, n), HU_MEMNUM_OVL, HEAP_MODEL)
#define M562_ABS(x) (((x) >= 0.0f) ? (x) : -(x))
#define M562_WRAP_D(a) ((a) > 180.0 ? (a) - 360.0 : ((a) <= -180.0 ? 360.0 + (a) : (a)))
#define M562_WRAP_F(a) ((a) > 180.0f ? (a) - 360.0f : ((a) <= -180.0f ? 360.0f + (a) : (a)))
#define M562_CLAMP(x, lo, hi) (((x) > (hi)) ? (hi) : (((x) < (lo)) ? (lo) : (x)))

/* --- functions (reference order), .data placed before its first user --- */
/* The frsqrte sequences are MSL's sqrtf inlined, but the reference pools 0.5 and 3.0 as ordinary
 * literals (0x5F8/0x600), not math.h's `static const double _half/_three` (m504 player.c precedent).
 * The host uses the real sqrtf. */
static inline float FireSqrtF(float x)
{
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        y = (float)(x * guess);
        return y;
    }
    return x;
}

/* 250 insns */
void fn_1_13CFC(M562_FIRE *fire, M562_WORK *work)
{
    M562_CAMERA *camera;
    M562_WORK *w;
    s32 i;
    s16 num;
    s16 model;
    M562_FIREOBJ *entry;
    float rand;

    w = work;
    camera = &w->camera[0];
    memset(fire, 0, sizeof(M562_FIRE));
    fire->unk0000 = work;
    fire->unk0004 = 0;
    fire->unk0008 = 0;
    fire->unk1104 = HuSprAnimRead(M562_DATA(108));
    for (i = 0; i < 6; i++) {
        fn_1_153A4(&fire->unk1108[i], fire);
    }
    switch (w->unk0020) {
        case 0:
            num = 35;
            break;
        case 1:
            num = 30;
            break;
        case 2:
            num = 25;
            break;
        case 3:
            num = 20;
            break;
    }
    fire->unk1100 = num;
    model = Hu3DModelCreate(M562_DATA(20));
    fire->unk1300 = model;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    fire->unk1302 = Hu3DJointMotion(model, M562_DATA(105));
    Hu3DMotionSet(model, fire->unk1302);
    Hu3DModelAttrReset(model, HU3D_MOTATTR_LOOP);
    for (i = 0; i < 35; i++) {
        entry = &fire->unk000C[i];
        fn_1_15D40(entry, i, fire);
        if (i >= num) {
            entry->unk10 = 7;
        }
        else {
            while (TRUE) {
                entry->unk44.y = 0.0f;
                rand = (frand() % 10000) / 10000.0f;
                entry->unk44.x = -625.0f + 1250.0f * rand;
                rand = (frand() % 10000) / 10000.0f;
                entry->unk44.z = -500.0f + 1000.0f * rand;
                if (FireSqrtF(entry->unk44.x * entry->unk44.x + entry->unk44.z * entry->unk44.z) > 200.0f) {
                    break;
                }
            }
        }
        if (i < 5) {
            entry->unk30 = 1;
        }
    }
    fn_1_2CD6C(&w->unk286C[0], 36);
    fn_1_2CE3C(&w->unk286C[0], fn_1_14390);
}

/* 43 insns */
void fn_1_140E4(M562_FIRE *fire)
{
    M562_WORK *work;
    s32 i;

    work = fire->unk0000;
    fn_1_2CDE8(&work->unk286C[0]);
    for (i = 0; i < 35; i++) {
        fn_1_16218(&fire->unk000C[i]);
    }
    Hu3DMotionKill(fire->unk1302);
    Hu3DModelKill(fire->unk1300);
    for (i = 0; i < 6; i++) {
        fn_1_154FC(&fire->unk1108[i]);
    }
    memset(fire, 0, sizeof(M562_FIRE));
}

/* 128 insns */
void fn_1_14190(M562_FIRE *fire)
{
    M562_WORK *work;
    M562_PLAYER *player;
    s32 i;
    M562_FIREOBJ *entry;
    float radius;
    HuVecF pos;

    work = fire->unk0000;
    player = &work->player;
    fire->unk1100 = 0;
    for (i = 0; i < 35; i++) {
        entry = &fire->unk000C[i];
        entry->unk08 = fire->unk0004;
        fn_1_16350(entry);
        if (entry->unk10 < 6) {
            fire->unk1100++;
        }
        if (entry->unk0C != 0 && player->unk130 != entry && entry->unk10 != 4 && entry->unk10 <= 5
            && !(entry->unk10 == 5 && entry->unk64 >= 0.0f)) {
            pos = entry->unk44;
            pos.y += 60.0f;
            radius = 60.0f;
            if (entry->unk10 == 5) {
                radius *= 1.3f;
            }
            fn_1_2CE8C(&work->unk286C[0], 1, 0, &pos, radius, entry);
        }
    }
    if (fire->unk0004 != 0) {
        radius = 0.5f * player->unk068;
        pos = player->unk0A0;
        pos.y += radius;
        fn_1_2CE8C(&work->unk286C[0], 0, 0, &pos, radius, player);
        fn_1_2CE44(&work->unk286C[0]);
    }
    for (i = 0; i < 6; i++) {
        fire->unk1108[i].unk14 = fire->unk0004;
        fn_1_15554(&fire->unk1108[i]);
    }
}

/* 42 insns */
void fn_1_14390(M562_HITENTRY *a, M562_HITENTRY *b)
{
    if (a->unk00 == 1 && b->unk00 == 1) {
        fn_1_14438(a->unk08, b->unk08);
    }
    else if (a->unk00 == 0 && b->unk00 == 1) {
        fn_1_14B68(a->unk08, b->unk08);
    }
    else if (a->unk00 == 1 && b->unk00 == 0) {
        fn_1_14B68(b->unk08, a->unk08);
    }
}

/* 460 insns */
void fn_1_14438(M562_FIREOBJ *a, M562_FIREOBJ *b)
{
    float ay;
    float by;
    float atop;
    float btop;
    float amid;
    float bmid;
    float ratio;
    float ha;
    float hb;
    float mag;
    float hmax;
    float dist;
    float hmin;
    HuVecF d;

    ay = a->unk44.y;
    atop = 120.0f + ay;
    by = b->unk44.y;
    btop = 120.0f + by;
    if (a->unk10 != 4 && a->unk12 != 4 && a->unk10 <= 5 && b->unk10 <= 5) {
    if (a->unk10 == 5) {
        fn_1_162A0(b);
    }
    if (b->unk10 == 5) {
        fn_1_162A0(a);
    }
    if ((ay >= by && atop <= btop) || (ay <= by && atop >= btop) || (atop >= by && atop <= btop)) {
        d.x = a->unk44.x - b->unk44.x;
        d.y = 0.0f;
        d.z = a->unk44.z - b->unk44.z;
        mag = VECMag(&d);
        if (mag < 100.0f) {
            if (d.x || d.z) {
                VECNormalize(&d, &d);
            }
            else {
                d.x = 0.0f;
                d.z = 1.0f;
            }
            a->unk38 = M562_WRAP_D(HuAtan(d.x, d.z));
            b->unk38 = M562_WRAP_D(HuAtan(-d.x, -d.z));
            VECScale(&d, &d, 100.0f - mag);
            amid = 0.5f * (ay + atop);
            bmid = 0.5f * (by + btop);
            ha = M562_ABS(amid - ay);
            hb = M562_ABS(bmid - by);
            hmax = (ha > hb) ? ha : hb;
            hmin = (ha > hb) ? hb : ha;
            dist = M562_ABS(amid - bmid);
            ratio = (dist < hmax) ? 1.0f : 1.0f - (dist - hmax) / hmin;
            a->unk44.x += 0.5f * d.x * ratio;
            a->unk44.z += 0.5f * d.z * ratio;
            b->unk44.x -= 0.5f * d.x * ratio;
            b->unk44.z -= 0.5f * d.z * ratio;
        }
    }
    }
}

/* 472 insns */
void fn_1_14B68(M562_PLAYER *player, M562_FIREOBJ *entry)
{
    float py;
    float ey;
    float ptop;
    float etop;
    float pmid;
    float emid;
    float ratio;
    float ha;
    float hb;
    float mag;
    float hmax;
    float dist;
    float hmin;
    HuVecF d;

    py = player->unk0A0.y;
    ptop = py + player->unk068;
    ey = entry->unk44.y;
    etop = 120.0f + ey;
    if (entry->unk10 > 3) {
        return;
    }
    if ((ptop == etop && py == ey) || (ptop <= etop && ptop >= ey) || (py <= etop && py >= ey) || (etop <= ptop && etop >= py)
        || (ey <= ptop && ey >= py)) {
        d.x = player->unk0A0.x - entry->unk44.x;
        d.y = 0.0f;
        d.z = player->unk0A0.z - entry->unk44.z;
        mag = VECMag(&d);
        if (mag < 110.0f) {
            if (d.x || d.z) {
                VECNormalize(&d, &d);
            }
            else {
                d.x = 0.0f;
                d.z = 1.0f;
            }
            entry->unk38 = M562_WRAP_D(HuAtan(-d.x, -d.z));
            VECScale(&d, &d, 110.0f - mag);
            if (entry->unk6C >= 3 && (player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0) {
                player->unk00A = 0;
                player->unk006 = 0;
                player->unk008 = 0;
                player->unk004 = 4;
            }
            pmid = 0.5f * (py + ptop);
            emid = 0.5f * (ey + etop);
            ha = M562_ABS(pmid - py);
            hb = M562_ABS(emid - ey);
            hmax = (ha > hb) ? ha : hb;
            hmin = (ha > hb) ? hb : ha;
            dist = M562_ABS(pmid - emid);
            ratio = (dist < hmax) ? 1.0f : 1.0f - (dist - hmax) / hmin;
            player->unk0A0.x += 0.5f * d.x * ratio;
            player->unk0A0.z += 0.5f * d.z * ratio;
            entry->unk44.x -= 0.5f * d.x * ratio;
            entry->unk44.z -= 0.5f * d.z * ratio;
            if (py > emid && mag < 88.0f) {
                if ((player->unk004 == 1 || player->unk004 == 2) && player->unk0C4 < 0.0f) {
                    player->unk0C4 = FireSqrtF(600.0f);
                    fn_1_AD68(player);
                    omVibrate(player->unk014, 10, 4, 2);
                }
                fn_1_162A0(entry);
            }
        }
    }
}

/* 16 insns */
void fn_1_152C8(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx)
{
    HU3DPARTICLEDATA *data;

    data = particleP->data;
    DCStoreRangeNoSync(particleP->data, particleP->maxCnt * sizeof(HU3DPARTICLEDATA));
}

/* 34 insns */
M562_FIRESLOT *fn_1_15308(M562_FIRE *fire, M562_FIREOBJ *entry)
{
    s32 i;
    M562_FIRESLOT *slot;

    for (i = 0; i < 6; i++) {
        slot = &fire->unk1108[i];
        if (slot->unk0C == 0 && slot->unk08 == 0) {
            slot->unk08 = 1;
            slot->unk20 = entry->unk44;
            slot->unk2C = entry->unk34;
            return slot;
        }
    }
    return NULL;
}

/* 5 insns */
void fn_1_15390(M562_FIRE *fire, M562_FIRESLOT *slot)
{
    slot->unk08 = 0;
    slot->unk4C = NULL;
}

/* 86 insns */
void fn_1_153A4(M562_FIRESLOT *slot, M562_FIRE *fire)
{
    s32 i;
    M562_FIRE *f;
    M562_WORK *work;
    M562_CAMERA *camera;
    s16 model;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;

    f = fire;
    work = f->unk0000;
    camera = &work->camera[0];
    memset(slot, 0, sizeof(M562_FIRESLOT));
    slot->unk00 = fire;
    slot->unk08 = 0;
    slot->unk0C = 0;
    slot->unk14 = 0;
    slot->unk18 = 0;
    slot->unk48 = -1;
    slot->unk50 = -1;
    model = Hu3DParticleCreate(f->unk1104, 12);
    slot->unk1C = model;
    Hu3DModelLayerSet(model, 4);
    Hu3DModelCameraSet(model, camera->unk04);
    Hu3DParticleHookSet(model, fn_1_152C8);
    Hu3DParticleBlendModeSet(model, 1);
    Hu3DParticleAnimModeSet(model, 0);
    particle = Hu3DData[model].hookData;
    particle->emitCnt = 0;
    particle->work = NULL;
    particle->count = 1;
    data = particle->data;
    for (i = 0; i < particle->maxCnt; data++, i++) {
        slot->unk30[i] = 0;
        data->cameraBit = camera->unk04;
        data->scale = 0.0f;
    }
}

/* 22 insns */
void fn_1_154FC(M562_FIRESLOT *slot)
{
    M562_FIRE *fire;
    M562_WORK *work;
    M562_BACK *back;

    fire = slot->unk00;
    work = fire->unk0000;
    back = &work->back;
    memset(slot, 0, sizeof(M562_FIRESLOT));
}

/* 0x998 */ u32 lbl_1_data_998[8] = { DATANUM(DATA_m562, 97), DATANUM(DATA_m562, 98), DATANUM(DATA_m562, 99), DATANUM(DATA_m562, 100), DATANUM(DATA_m562, 101), DATANUM(DATA_m562, 102), DATANUM(DATA_m562, 103), DATANUM(DATA_m562, 104) };
/* 0x9B8 */ HuVecF lbl_1_data_9B8[2] = { { 0.0f, 7000.0f, 0.0f }, { 0.0f, -1.0f, 0.02f } };
/* 0x9D0 */ GXColor lbl_1_data_9D0 = { 0xA0, 0x10, 0x00, 0xFF };

/* 393 insns */
void fn_1_15554(M562_FIRESLOT *slot)
{
    M562_FIRE *fire;
    M562_WORK *work;
    M562_BACK *back;
    M562_CAMERA *camera;
    s32 i;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 count;
    s32 spawned;
    s16 model;
    float t;
    float pan;
    GXColor color;
    HuVecF pos;
    HuVecF scr;

    fire = slot->unk00;
    work = fire->unk0000;
    back = &work->back;
    camera = &work->camera[0];
    if (slot->unk14 != 0 && slot->unk18 == 0) {
        slot->unk18 = 1;
    }
    else if (slot->unk14 == 0 && slot->unk18 != 0) {
        particle = Hu3DData[slot->unk1C].hookData;
        data = particle->data;
        for (i = 0; i < particle->maxCnt; data++, i++) {
            data->scale = 0.0f;
        }
        slot->unk18 = 0;
    }
    if (slot->unk18 != 0 && slot->unk10 == 0) {
        if (slot->unk0C == 0) {
            if (slot->unk08 != 0) {
                slot->unk0C = 1;
                if (slot->unk50 < 0) {
                    slot->unk50 = fn_1_814(0x8A0);
                }
            }
            else {
                if (slot->unk50 >= 0) {
                    fn_1_83C(slot->unk50);
                    slot->unk50 = -1;
                }
                return;
            }
        }
        if (slot->unk0C != 0 && slot->unk50 >= 0) {
            Hu3D3Dto2D(&slot->unk20, 2, &scr);
            pan = 2.0f * (scr.x / 576.0f - 0.5f);
            pan = 64.0f + 32.0f * pan;
            fn_1_894(slot->unk50, pan);
        }
        model = slot->unk1C;
        particle = Hu3DData[model].hookData;
        data = particle->data;
        spawned = 0;
        count = 0;
        for (i = 0; i < particle->maxCnt; data++, i++) {
            if (slot->unk30[i] != 0) {
                t = slot->unk30[i] / 30.0f;
                pos.x = slot->unk20.x + (30.0f + 100.0f * t) * HuSin(slot->unk2C);
                pos.y = 40.0f + slot->unk20.y + 10.0f * ((1.0f - t) * (1.0f - t));
                pos.z = slot->unk20.z + (30.0f + 100.0f * t) * HuCos(slot->unk2C);
                data->cameraBit = camera->unk04;
                data->scale = 20.0f + 60.0f * (t * t) + 10.0f * ((frand() % 10000) / 10000.0f);
                data->color.r = 96.0f + 32.0f * (1.0f - t);
                data->color.g = 64.0f + 64.0f * (1.0f - t);
                data->color.b = 64.0f + 64.0f * (1.0f - t);
                data->color.a = 255;
                data->pos.x = pos.x;
                data->pos.y = pos.y;
                data->pos.z = pos.z;
                if (slot->unk30[i]++ > 30) {
                    slot->unk30[i] = 0;
                    data->scale = 0.0f;
                }
                count++;
            }
            else {
                if (slot->unk08 != 0 && spawned == 0 && slot->unk06 % 3 == 0) {
                    slot->unk30[i] = 1;
                    spawned = 1;
                }
                data->scale = 0.0f;
            }
        }
        if (count != 0) {
            color = lbl_1_data_9D0;
            fn_1_15B78(slot);
        }
        if (count == 0 && slot->unk08 == 0 && slot->unk0C != 0) {
            slot->unk0C = 0;
        }
        slot->unk06++;
    }
}

/* 114 insns */
void fn_1_15B78(M562_FIRESLOT *slot)
{
    M562_PLAYER *player;
    M562_FIRE *fire;
    M562_WORK *work;
    float mag;
    float dot;
    HuVecF d;
    HuVecF n;
    HuVecF dir;

    fire = slot->unk00;
    work = fire->unk0000;
    player = &work->player;
    if ((player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0) {
        VECSubtract(&player->unk0A0, &slot->unk20, &d);
        mag = VECMag(&d);
        if (mag < 170.0f) {
            if (!d.x && !d.z) {
                d.z = 1.0f;
            }
            VECNormalize(&d, &n);
            dir.x = HuSin(slot->unk2C);
            dir.y = 0.0f;
            dir.z = HuCos(slot->unk2C);
            dot = VECDotProduct(&n, &dir);
            if (dot >= HuCos(30.0)) {
                player->unk00A = 0;
                player->unk006 = 0;
                player->unk008 = 0;
                player->unk004 = 4;
            }
        }
    }
}

/* 310 insns */
void fn_1_15D40(M562_FIREOBJ *entry, s16 index, M562_FIRE *fire)
{
    M562_FIRE *f;
    M562_WORK *work;
    M562_CAMERA *camera;
    s32 i;
    s16 model;
    s16 shadow;
    float t;

    f = fire;
    work = f->unk0000;
    camera = &work->camera[0];
    memset(entry, 0, sizeof(M562_FIREOBJ));
    entry->unk00 = fire;
    entry->unk08 = entry->unk0C = 0;
    entry->unk04 = index;
    if (index == 0) {
        model = Hu3DModelCreate(M562_DATA(19));
        entry->unk1C = model;
        shadow = Hu3DModelCreate(M562_DATA(21));
        entry->unk2E = shadow;
    }
    else {
        model = Hu3DModelLink(entry->unk00->unk000C[0].unk1C);
        entry->unk1C = model;
        shadow = Hu3DModelLink(entry->unk00->unk000C[0].unk2E);
        entry->unk2E = shadow;
    }
    t = (frand() % 10000) / 10000.0f;
    entry->unk38 = entry->unk34 = entry->unk50.y = M562_WRAP_F(360.0f * (t - 0.5f));
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, entry->unk34, 0.0f);
    Hu3DModelCameraSet(model, camera->unk04);
    Hu3DModelLayerSet(model, 3);
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(shadow, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(shadow, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(shadow, 0.8f, 0.8f, 0.8f);
    Hu3DModelCameraSet(shadow, camera->unk04);
    Hu3DModelLayerSet(shadow, 3);
    Hu3DModelAttrSet(shadow, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 8; i++) {
        if (index == 0) {
            entry->unk1E[i] = Hu3DJointMotion(model, HuDataSelHeapReadNum(lbl_1_data_998[i], HU_MEMNUM_OVL, HEAP_MODEL));
        }
        else {
            entry->unk1E[i] = entry->unk00->unk000C[0].unk1E[i];
        }
    }
    Hu3DMotionSet(model, entry->unk1E[0]);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
    entry->unk3C = entry->unk3E = 0;
    entry->unk40 = 1;
    model = Hu3DModelLink(f->unk1300);
    entry->unk74 = model;
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(model, 0.5f, 0.5f, 0.5f);
    Hu3DModelCameraSet(model, camera->unk04);
    Hu3DModelLayerSet(model, 4);
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(model, f->unk1302);
    Hu3DModelAttrReset(model, HU3D_MOTATTR_LOOP);
}

/* 34 insns */
void fn_1_16218(M562_FIREOBJ *entry)
{
    s32 i;

    Hu3DModelKill(entry->unk74);
    if (entry->unk04 == 0) {
        for (i = 0; i < 8; i++) {
            Hu3DMotionKill(entry->unk1E[i]);
        }
    }
    Hu3DModelKill(entry->unk2E);
    Hu3DModelKill(entry->unk1C);
    memset(entry, 0, sizeof(M562_FIREOBJ));
}

/* 44 insns */
void fn_1_162A0(M562_FIREOBJ *entry)
{
    M562_FIRE *fire;
    M562_WORK *work;
    M562_FIRESLOT *slot;

    fire = entry->unk00;
    work = fire->unk0000;
    if (entry->unk10 < 6) {
        if (entry->unk68 != 0) {
            slot = entry->unk68;
            slot->unk08 = 0;
            slot->unk4C = NULL;
            entry->unk68 = NULL;
            entry->unk6E = 0;
            entry->unk6C = 0;
        }
        if (work->unk000C == 4) {
            fn_1_814(0x8A1);
        }
        entry->unk14 = 13;
        entry->unk10 = 6;
    }
}

/* 0x9D1 */ /* lbl_1_data_9D1: the last three bytes of the GXColor above (dtk split) */

/* 476 insns */
void fn_1_16350(M562_FIREOBJ *entry)
{
    M562_FIRE *fire;
    M562_WORK *work;
    M562_PLAYER *player;
    s32 attr;
    s16 model;
    float maxTime;

    fire = entry->unk00;
    work = fire->unk0000;
    player = &work->player;
    if (entry->unk08 != 0 && entry->unk0C == 0) {
        Hu3DModelAttrReset(entry->unk1C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(entry->unk2E, HU3D_ATTR_DISPOFF);
        entry->unk0C = 1;
    }
    else if (entry->unk08 == 0 && entry->unk0C != 0) {
        Hu3DModelAttrSet(entry->unk1C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(entry->unk2E, HU3D_ATTR_DISPOFF);
        entry->unk0C = 0;
    }
    if (entry->unk0C == 0) {
        return;
    }
    if (fire->unk0008 == 0) {
        if (entry->unk10 < 4) {
            entry->unk10 = 1;
            entry->unk14 = 1;
        }
        if (entry->unk68 != 0) {
            fn_1_15390(fire, entry->unk68);
            entry->unk68 = NULL;
            entry->unk6E = 0;
            entry->unk6C = 0;
        }
    }
    switch (entry->unk10) {
        case 0:
            if (entry->unk08 != 0) {
                Hu3DModelAttrReset(entry->unk1C, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(entry->unk2E, HU3D_ATTR_DISPOFF);
            }
            if (entry->unk30 != 0) {
                entry->unk14 = frand() % 60 + 60;
                entry->unk10 = 3;
                if (entry->unk70 > 180 && frand() % 10000 < 2000) {
                    if (entry->unk6C == 0) {
                        entry->unk6C = 1;
                        entry->unk14 = 180;
                    }
                    entry->unk70 = 0;
                }
            }
            else {
                entry->unk14 = frand() % 90 + 90;
                if (frand() & 1) {
                    entry->unk10 = 1;
                    if (entry->unk70 > 180 && frand() % 10000 < 2000) {
                        if (entry->unk6C == 0) {
                            entry->unk6C = 1;
                            entry->unk14 = 180;
                        }
                        entry->unk70 = 0;
                    }
                }
                else {
                    entry->unk10 = 2;
                }
            }
            entry->unk12 = 0;
            entry->unk16 = 0;
            break;
        case 1:
            fn_1_16CF4(entry);
            if (--entry->unk14 <= 0) {
                entry->unk14 = 0;
                entry->unk10 = 0;
            }
            break;
        case 2:
            fn_1_16D08(entry);
            if (--entry->unk14 <= 0) {
                entry->unk14 = 0;
                entry->unk10 = 0;
            }
            break;
        case 3:
            fn_1_170E0(entry);
            if (--entry->unk14 <= 0) {
                entry->unk14 = 0;
                entry->unk10 = 0;
            }
            break;
        case 4:
            fn_1_1776C(entry);
            break;
        case 5:
            if (fn_1_174C0(entry)) {
                fn_1_162A0(entry);
            }
            break;
        case 6:
            entry->unk3E = 5;
            entry->unk40 = 0;
            if (entry->unk14-- <= 0) {
                Hu3DMotionTimeSet(entry->unk74, 0.0f);
                Hu3DModelPosSet(entry->unk74, entry->unk44.x, entry->unk44.y, entry->unk44.z - 10.0f);
                Hu3DModelAttrReset(entry->unk74, HU3D_ATTR_DISPOFF);
                entry->unk78 = 1;
                Hu3DModelAttrSet(entry->unk1C, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(entry->unk2E, HU3D_ATTR_DISPOFF);
                entry->unk14 = 0;
                entry->unk10 = 7;
            }
            break;
        case 7:
            Hu3DModelAttrSet(entry->unk1C, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(entry->unk2E, HU3D_ATTR_DISPOFF);
            break;
    }
    fn_1_16AC0(entry);
    model = entry->unk1C;
    if (entry->unk3C != entry->unk3E && Hu3DMotionShiftIDGet(model) < 0) {
        entry->unk3C = entry->unk3E;
        Hu3DModelAttrReset(model, HU3D_MOTATTR_LOOP);
        if (entry->unk40 != 0) {
            attr = HU3D_MOTATTR_LOOP;
        }
        else {
            attr = 0;
        }
        Hu3DMotionShiftSet(model, entry->unk1E[entry->unk3C], 0.0f, 4.0f, attr);
    }
    if (entry != player->unk130) {
        if (entry->unk10 < 5) {
            entry->unk64 -= 1.5f;
            entry->unk44.y += entry->unk64;
            if (entry->unk44.y <= 0.0f) {
                entry->unk44.y = 0.0f;
                entry->unk64 = 0.0f;
            }
        }
        entry->unk44.x = M562_CLAMP(entry->unk44.x, -625.0f, 625.0f);
        entry->unk44.z = M562_CLAMP(entry->unk44.z, -500.0f, 500.0f);
    }
    Hu3DModelPosSet(model, entry->unk44.x, entry->unk44.y, entry->unk44.z);
    Hu3DModelRotSet(model, entry->unk50.x, entry->unk50.y, entry->unk50.z);
    if (entry->unk10 == 4) {
        Hu3DModelPosSet(entry->unk2E, player->unk0A0.x, 5.0f, player->unk0A0.z);
    }
    else {
        Hu3DModelPosSet(entry->unk2E, entry->unk44.x, 5.0f, entry->unk44.z);
    }
    if (entry->unk78 != 0) {
        model = entry->unk74;
        maxTime = Hu3DMotionMaxTimeGet(model);
        if (Hu3DMotionTimeGet(model) >= maxTime) {
            Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
            entry->unk78 = 0;
        }
    }
}

/* 141 insns */
void fn_1_16AC0(M562_FIREOBJ *entry)
{
    M562_FIRE *fire;
    M562_FIRESLOT *slot;

    fire = entry->unk00;
    switch (entry->unk6C) {
        case 0:
            break;
        case 1:
            slot = fn_1_15308(fire, entry);
            if (slot == 0) {
                entry->unk6E = 0;
                entry->unk6C = 0;
                break;
            }
            entry->unk68 = slot;
            entry->unk72 = entry->unk3C;
            slot->unk4C = entry;
            slot->unk10 = 1;
            entry->unk6E = 60;
            entry->unk6C++;
        case 2:
            entry->unk3E = (entry->unk10 == 1) ? 3 : 6;
            entry->unk40 = 1;
            if (--entry->unk6E <= 0) {
                entry->unk68->unk10 = 0;
                entry->unk6E = 90;
                entry->unk6C++;
            }
            break;
        case 3:
            if (entry->unk68 != 0) {
                entry->unk68->unk20 = entry->unk44;
                entry->unk68->unk2C = entry->unk34;
            }
            entry->unk3E = (entry->unk10 == 1) ? 4 : 7;
            entry->unk40 = 1;
            if (--entry->unk6E <= 0) {
                entry->unk3E = entry->unk72;
                entry->unk40 = 1;
                fn_1_15390(fire, entry->unk68);
                entry->unk68 = NULL;
                entry->unk6E = 0;
                entry->unk6C = 0;
            }
            break;
    }
    entry->unk70++;
}

/* 5 insns */
void fn_1_16CF4(M562_FIREOBJ *entry)
{
    entry->unk3E = 0;
    entry->unk40 = 1;
}

/* 246 insns */
void fn_1_16D08(M562_FIREOBJ *entry)
{
    float t;
    HuVecF vel;

    entry->unk3E = 2;
    entry->unk40 = 1;
    switch (entry->unk12) {
        case 0:
            t = (frand() % 10000) / 10000.0f;
            entry->unk38 = M562_WRAP_F(entry->unk34 + 120.0f * (t - 0.5f));
            entry->unk16 = frand() % 90 + 90;
            entry->unk12 = 1;
            break;
        case 1:
            if (entry->unk44.z <= -500.0f) {
                entry->unk38 = 0.0f;
            }
            else if (entry->unk44.z >= 500.0f) {
                entry->unk38 = 180.0f;
            }
            if (entry->unk44.x <= -625.0f) {
                entry->unk38 = 90.0f;
            }
            else if (entry->unk44.x >= 625.0f) {
                entry->unk38 = -90.0f;
            }
            if (entry->unk16-- <= 0) {
                entry->unk16 = 0;
                entry->unk12 = 0;
            }
            break;
    }
    entry->unk34 = fn_1_36EC(entry->unk38, entry->unk34, 0.95f);
    vel.x = 7.0 * HuSin(entry->unk34);
    vel.z = 7.0 * HuCos(entry->unk34);
    entry->unk44.x += vel.x;
    entry->unk44.z += vel.z;
    entry->unk50.y = entry->unk34;
}

/* 248 insns */
void fn_1_170E0(M562_FIREOBJ *entry)
{
    M562_FIRE *fire;
    M562_WORK *work;
    M562_PLAYER *player;
    float speed;
    float dist;
    HuVecF d;

    fire = entry->unk00;
    work = fire->unk0000;
    player = &work->player;
    speed = 7.0f;
    entry->unk3E = 2;
    entry->unk40 = 1;
    VECSubtract(&player->unk0A0, &entry->unk44, &d);
    d.y = 0.0f;
    dist = VECMag(&d);
    if (d.x || d.z) {
        VECNormalize(&d, &d);
    }
    entry->unk38 = M562_WRAP_D(HuAtan(d.x, d.z));
    if (entry->unk44.z <= -500.0f) {
        entry->unk38 = 0.0f;
    }
    else if (entry->unk44.z >= 500.0f) {
        entry->unk38 = 180.0f;
    }
    if (entry->unk44.x <= -625.0f) {
        entry->unk38 = 90.0f;
    }
    else if (entry->unk44.x >= 625.0f) {
        entry->unk38 = -90.0f;
    }
    if (dist < 300.0f) {
        entry->unk3E = 0;
        entry->unk40 = 1;
        speed = 0.0f;
    }
    entry->unk34 = fn_1_36EC(entry->unk38, entry->unk34, 0.95f);
    d.x = speed * HuSin(entry->unk34);
    d.z = speed * HuCos(entry->unk34);
    entry->unk44.x += d.x;
    entry->unk44.z += d.z;
    entry->unk50.y = entry->unk34;
}

/* 171 insns */
s32 fn_1_174C0(M562_FIREOBJ *entry)
{
    M562_FIRE *fire;
    M562_WORK *work;
    M562_PLAYER *player;
    s32 ret;
    HuVecF vel;

    fire = entry->unk00;
    work = fire->unk0000;
    player = &work->player;
    ret = 0;
    switch (entry->unk12) {
        case 0:
            entry->unk3E = 0;
            entry->unk40 = 1;
            entry->unk64 = FireSqrtF(600.0f);
            entry->unk38 = entry->unk34 = player->unk090;
            entry->unk12 = 1;
            break;
        case 1:
            entry->unk64 -= 1.5f;
            entry->unk44.y += entry->unk64;
            if (entry->unk64 < 0.0f && entry->unk44.y <= 0.0f) {
                entry->unk50.x = entry->unk50.z = 0.0f;
                entry->unk44.y = 0.0f;
                ret = 1;
            }
            break;
    }
    vel.x = 14.0 * HuSin(entry->unk34);
    vel.z = 14.0 * HuCos(entry->unk34);
    entry->unk44.x += vel.x;
    entry->unk44.z += vel.z;
    entry->unk50.y = entry->unk34;
    return ret;
}

/* 32 insns */
s32 fn_1_1776C(M562_FIREOBJ *entry)
{
    M562_FIRE *fire;
    M562_WORK *work;
    M562_PLAYER *player;

    fire = entry->unk00;
    work = fire->unk0000;
    player = &work->player;
    entry->unk3E = 0;
    entry->unk40 = 1;
    if (entry->unk68 != 0) {
        fn_1_15390(fire, entry->unk68);
        entry->unk68 = NULL;
        entry->unk6E = 0;
        entry->unk6C = 0;
    }
    return 0;
}
