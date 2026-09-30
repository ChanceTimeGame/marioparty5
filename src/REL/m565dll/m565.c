/*
 * m565dll m565.c -- written 2026-09-23 (W1 forks; see NOTES.md). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m565dll/asm/REL/m565dll/m565.s.
 */

#include "REL/m565dll.h"

#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hsfex.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* float lbl_1_rodata_10 = -55.0f; */
/* 0x14 */ /* float lbl_1_rodata_14 = 0.0f; */
/* 0x18 */ /* float lbl_1_rodata_18 = 20.0f; */
/* 0x1C */ /* float lbl_1_rodata_1C = 1800.0f; */
/* 0x20 */ /* float lbl_1_rodata_20 = 45.0f; */
/* 0x24 */ /* float lbl_1_rodata_24 = 15000.0f; */
/* 0x28 */ /* float lbl_1_rodata_28 = 1.2f; */
/* 0x2C */ /* float lbl_1_rodata_2C = 640.0f; */
/* 0x30 */ /* float lbl_1_rodata_30 = 480.0f; */
/* 0x34 */ /* float lbl_1_rodata_34 = 1.0f; */
/* 0x38 */ /* float lbl_1_rodata_38 = -2.0f; */
/* 0x3C */ /* float lbl_1_rodata_3C = 5.0f; */
/* 0x40 */ /* double lbl_1_rodata_40 = 360; */
/* 0x48 */ /* float lbl_1_rodata_48 = 360.0f; */
/* 0x4C */ /* float lbl_1_rodata_4C = 180.0f; */
/* 0x50 */ /* float lbl_1_rodata_50 = 2.0f; */
/* 0x54 */ /* float lbl_1_rodata_54 = 576.0f; */
/* 0x58 */ /* float lbl_1_rodata_58 = 0.5f; */
/* 0x5C */ /* float lbl_1_rodata_5C = -1.0f; */
/* 0x60 */ /* float lbl_1_rodata_60 = -550.0f; */
/* 0x64 */ /* float lbl_1_rodata_64 = 1100.0f; */
/* 0x68 */ /* float lbl_1_rodata_68 = 64.0f; */
/* 0x6C */ /* float lbl_1_rodata_6C = 16.0f; */
/* 0x70 */ /* float lbl_1_rodata_70 = 96.0f; */
/* 0x74 */ /* float lbl_1_rodata_74 = 31.0f; */

/* --- .data --- */
/* 0x0 */ s32 lbl_1_data_0 = 1;
/* 0x4 */ MGSEQ_PARAM lbl_1_data_4 = { 60, 0, fn_1_3C8, fn_1_498, fn_1_4EC, fn_1_59C, fn_1_5EC, fn_1_820, fn_1_864, fn_1_8B8, fn_1_43C };
/* 0x2C */ s32 lbl_1_data_2C[1] = { 0 }; /* dtk gap_04 tail: unreferenced zero word */
/* 0x30 */ HuVecF lbl_1_data_30 = { 1000.0f, 7000.0f, 1000.0f }; /* Hu3DShadowPosSet pos */
/* 0x3C */ HuVecF lbl_1_data_3C = { 0.0f, 0.0f, -1.0f }; /* Hu3DShadowPosSet up */
/* 0x48 */ HuVecF lbl_1_data_48 = { 0.0f, 0.0f, 0.0f }; /* Hu3DShadowPosSet target */
/* 0x54 */ s32 lbl_1_data_54[1] = { 0 }; /* dtk folds this unreferenced zero word into lbl_1_data_48 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x4 */ OMOBJMAN *lbl_1_bss_4; /* MgActorObjectSetup() */
/* 0x0 */ M565_WORK *lbl_1_bss_0; /* the work block (stage.c reads it too) */

/* --- functions (reference order) --- */
/* 12 insns */
void fn_1_0(M565_LIST *list)
{
    memset(list, 0, sizeof(M565_LIST));
}

/* 28 insns */
void fn_1_30(M565_LIST *list)
{
    M565_LISTNODE *node;
    M565_LISTNODE *next;

    for (node = list->unk004; node; node = next) {
        next = node->unk004;
        memset(node, 0, sizeof(M565_LISTNODE));
    }
    memset(list, 0, sizeof(M565_LIST));
}

/* 17 insns */
void fn_1_A0(M565_LIST *list, M565_LISTNODE *node, void *data)
{
    node->unk000 = data;
    if (!list->unk004) {
        list->unk004 = node;
        list->unk008 = node;
    } else {
        list->unk008->unk004 = node;
        node->unk008 = list->unk008;
        list->unk008 = node;
    }
    node->unk00C = list;
    list->unk000++;
}

/* 39 insns */
void fn_1_E4(M565_LIST *list, M565_LISTNODE *node)
{
    if (node == list->unk004) {
        list->unk004 = node->unk004;
        if (list->unk004) {
            list->unk004->unk008 = NULL;
        }
    } else if (node == list->unk008) {
        list->unk008 = node->unk008;
        if (list->unk008) {
            list->unk008->unk004 = NULL;
        }
    } else {
        node->unk008->unk004 = node->unk004;
        node->unk004->unk008 = node->unk008;
    }
    node->unk00C = NULL;
    node->unk004 = node->unk008 = NULL;
    list->unk000--;
}

/* 106 insns */
void ObjectSetup(void)
{
    lbl_1_bss_4 = MgActorObjectSetup();
    CRot.x = -55.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 20.0f;
    CZoom = 1800.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    omAddObjEx(lbl_1_bss_4, 0x7FDA, 0, 0, -1, omOutView);
    MgSeqCreate(&lbl_1_data_4);
    MgSeqModeHookAdd(MGSEQ_MODE_PREMAIN, fn_1_548);
}

/* 29 insns */
void fn_1_3C8(s16 mode, s16 frameNo)
{
    M565_WORK *work;

    work = lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M565_WORK), HU_MEMNUM_OVL);
    memset(lbl_1_bss_0, 0, sizeof(M565_WORK));
    fn_1_E48(work, lbl_1_bss_4);
    MgSeqModeNext();
}

/* 23 insns */
void fn_1_43C(s16 mode, s16 frameNo)
{
    M565_WORK *work = lbl_1_bss_0;

    fn_1_F48(work);
    HuMemDirectFree(lbl_1_bss_0);
    lbl_1_bss_0 = NULL;
    MgSeqModeNext();
}

/* 21 insns */
void fn_1_498(s16 mode, s16 frameNo)
{
    M565_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    if (fn_1_104C(work)) {
        MgSeqModeNext();
    }
    fn_1_FA8(work, 0);
}

/* 23 insns */
void fn_1_4EC(s16 mode, s16 frameNo)
{
    M565_WORK *work = lbl_1_bss_0;
    GAMEMESID mesId = MgSeqGameMesIdGet();

    if (work->unk3878 < 0) {
        work->unk3878 = fn_1_DC8(55);
    }
    fn_1_FA8(work, 0);
}

/* 21 insns */
void fn_1_548(s16 mode, s16 frameNo)
{
    M565_WORK *work = lbl_1_bss_0;

    fn_1_1074(work);
    fn_1_FA8(work, 0);
    lbl_1_data_0 = 1;
}

/* 20 insns */
void fn_1_59C(s16 mode, s16 frameNo)
{
    M565_WORK *work = lbl_1_bss_0;

    work->unk3870 = 1;
    if (fn_1_FA8(work, 1)) {
        MgSeqModeNext();
    }
}

/* 141 insns */
void fn_1_5EC(s16 mode, s16 frameNo)
{
    M565_WORK *work = lbl_1_bss_0;
    M565_OBJECT *obj = &work->unk018;
    M565_STAGE *stage = &obj->unk2E4;
    GAMEMESID mesId;
    s32 i;
    M565_PLAYER *player;
    M565_PUKU2OBJ *puku;
    M565_STAGEGRID *cell;

    if (lbl_1_data_0) {
        for (i = 0; i < 4; i++) {
            player = &work->unk018.unk008[i];
            player->unk094 = 0;
            if (player->unk090 == 0) {
                cell = &stage->unk004[player->unk08A][player->unk088];
                if ((cell->unk004 == 100 || cell->unk004 == 101) && player->unk004->mode == MGPLAYER_MODE_WALK
                    && player->unk074->y >= -2.0f && player->unk074->y < 5.0f) {
                    fn_1_8984(player, 0);
                    Hu3DMotionSet(player->unk010, player->unk012[0]);
                    Hu3DModelAttrSet(player->unk010, HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrReset(player->unk010, HU3D_ATTR_DISPOFF);
                    Hu3DModelScaleSet(player->unk010, 1.0f, 1.0f, 1.0f);
                }
            }
        }
        for (i = 0; i < 5; i++) {
            puku = &obj->unk3648.unk004[i];
            if (puku->unk004 != 0) {
                puku->unk02C = 1;
                puku->unk058 = 60;
            }
        }
        /* retail: vibrate-kill only the last player the loop left in `player` (i == 3) */
        MgPlayerVibrateKill(player->unk004);
        lbl_1_data_0 = 0;
        work->unk00E = 0;
    }
    mesId = MgSeqGameMesIdGet();
    if (work->unk3878 >= 0 && (GameMesStatGet(mesId) & GAMEMES_STAT_FXPLAY)) {
        fn_1_D78(work->unk3878, 100);
        work->unk3878 = -1;
        if (stage->unk3354 >= 0) {
            fn_1_C40(stage->unk3354);
            stage->unk3354 = -1;
        }
    }
    work->unk3870 = 0;
    fn_1_FA8(work, 0);
}

/* 17 insns */
void fn_1_820(s16 mode, s16 frameNo)
{
    M565_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    MgSeqModeNext();
    fn_1_FA8(work, 0);
}

/* 21 insns */
void fn_1_864(s16 mode, s16 frameNo)
{
    M565_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    if (fn_1_10E0(work)) {
        MgSeqModeNext();
    }
    fn_1_FA8(work, 0);
}

/* 15 insns */
void fn_1_8B8(s16 mode, s16 frameNo)
{
    M565_WORK *work = lbl_1_bss_0;

    fn_1_FA8(work, 0);
}

/* 71 insns; = m503 fn_1_2B7C / m510 fn_1_2840 */
float fn_1_8F4(float cur, float target, float rate)
{
    float d;
    float e;
    float r;

    d = fmod(target - cur, 360.0);
    r = d;
    if (r < 0.0f) {
        r += 360.0f;
    }
    if (r > 180.0f) {
        r -= 360.0f;
    }
    e = fmod(cur + rate * r, 360.0);
    r = e;
    if (r < 0.0f) {
        r += 360.0f;
    }
    return r;
}

/* 130 insns: screen-x -> pan 48..80, depth -> volume 96..127 (both clamped) */
void fn_1_A10(HuVecF *pos, float *vol, float *pan)
{
    HuVecF pos2d;
    float x;
    float z;
    float v;

    Hu3D3Dto2D(pos, 1, &pos2d);
    x = 2.0f * (pos2d.x / 576.0f - 0.5f);
    x = (x > 1.0f) ? 1.0f : ((x < -1.0f) ? -1.0f : x);
    z = (pos->z - -550.0f) / 1100.0f;
    z = (z > 1.0f) ? 1.0f : ((z < 0.0f) ? 0.0f : z);
    x = 64.0f + 16.0f * x;
    v = 96.0f + 31.0f * z;
    *vol = v;
    *pan = x;
}

/* audio wrappers: = m502 fn_1_198 .. fn_1_368 (plus HuAudFXVolSet at C98) */
/* 10 insns */
int fn_1_C18(int seId)
{
    return HuAudFXPlay(seId);
}

/* 10 insns */
void fn_1_C40(int seNo)
{
    HuAudFXStop(seNo);
}

/* 12 insns */
void fn_1_C68(int seNo, s32 speed)
{
    HuAudFXFadeOut(seNo, speed);
}

/* 12 insns */
void fn_1_C98(int seNo, s16 pan)
{
    HuAudFXPanning(seNo, pan);
}

/* 12 insns */
void fn_1_CC8(int seNo, s16 vol)
{
    HuAudFXVolSet(seNo, vol);
}

/* 22 insns */
void fn_1_CF8(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis)
{
    HuAudFXListnerSetEX(pos, heading, sndDist, sndSpeed, startDis, frontSurDis, backSurDis);
}

/* 10 insns */
int fn_1_D50(s16 streamId)
{
    return HuAudSStreamPlay(streamId);
}

/* 12 insns */
void fn_1_D78(int streamNo, s32 speed)
{
    HuAudSStreamFadeOut(streamNo, speed);
}

/* 8 insns */
void fn_1_DA8(void)
{
    HuAudAllStop();
}

/* 10 insns */
int fn_1_DC8(s16 streamId)
{
    return HuAudBGMPlay(streamId);
}

/* 10 insns */
int fn_1_DF0(s16 streamId)
{
    return HuAudJinglePlay(streamId);
}

/* 12 insns */
int fn_1_E18(s16 streamId, s16 chanNo)
{
    return HuAudSStreamChanPlay(streamId, chanNo);
}
