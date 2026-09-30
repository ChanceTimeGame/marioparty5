/*
 * m562dll m562.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/m562.s.
 */

#include "REL/m562dll.h"

#include "game/audio.h"
#include "game/frand.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/gamemes.h"
#include "game/printfunc.h"
#include "math.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#include "game/esprite.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const float lbl_1_rodata_10 = 1.0f; /* 0x10 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x4 */ OMOBJMAN *lbl_1_bss_4;
/* 0x0 */ M562_WORK *lbl_1_bss_0;

/* --- functions (reference order), .data placed before its first user --- */
/* 0x0 */ s32 lbl_1_data_0[1] = { 0x1 };
/* 0x4 */ s32 lbl_1_data_4[1] = { 0x1 };
/* 0x8 */ MGSEQ_PARAM lbl_1_data_8 = { 0, 2, fn_1_E8, fn_1_20C, fn_1_2D0, fn_1_410, fn_1_460, fn_1_5DC, fn_1_6DC, fn_1_7C8, fn_1_1B0 };

void ObjectSetup(void)
{
    lbl_1_bss_4 = MgActorObjectSetup();
    MgSeqCreate(&lbl_1_data_8);
    MgSeqModeHookAdd(MGSEQ_MODE_PREMAIN, fn_1_380);
}

/* INIT */
void fn_1_E8(s16 mode, s16 frameNo)
{
    M562_WORK *work;

    work = lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M562_WORK), HU_MEMNUM_OVL);
    memset(lbl_1_bss_0, 0, sizeof(M562_WORK));
    fn_1_AC4(work, lbl_1_bss_4);
    work->unk000C = 0;
    work->unk000E = 1;
    fn_1_16F0(work, 0);
    fn_1_22694(&work->light, 0, 1.0f);
    fn_1_4748(&work->back, 0, 1.0f);
    MgSeqStatBitReset(MGSEQ_STAT_FADEIN_OFF);
    MgSeqModeNext();
}

/* CLOSE */
void fn_1_1B0(s16 mode, s16 frameNo)
{
    M562_WORK *work = lbl_1_bss_0;

    fn_1_FB0(work);
    HuMemDirectFree(lbl_1_bss_0);
    lbl_1_bss_0 = NULL;
    MgSeqModeNext();
}

/* FADEIN: runs the phase's event, then sets the phase up */
void fn_1_20C(s16 mode, s16 frameNo)
{
    M562_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    if (fn_1_1F54(work)) {
        switch (work->unk000E) {
        case 1:
            fn_1_16F0(work, 0);
            break;
        case 2:
            fn_1_16F0(work, 1);
            break;
        case 3:
            fn_1_16F0(work, 2);
            break;
        case 4:
            fn_1_16F0(work, 3);
            break;
        }
        MgSeqModeNext();
    }
    work->unk000C = 1;
    fn_1_1330(work, 0);
}

/* START */
void fn_1_2D0(s16 mode, s16 frameNo)
{
    M562_WORK *work = lbl_1_bss_0;

    if (work->unk000E == 1 && work->unk28A8 < 0) {
        work->unk28A8 = fn_1_A44(0x40);
        fn_1_9BC(work->unk28A8, 127, 0);
    } else if (work->unk000E == 4 && work->unk28A8 < 0) {
        work->unk28A8 = fn_1_A44(0x41);
        fn_1_9BC(work->unk28A8, 127, 0);
    }
    work->unk000C = 2;
    fn_1_1330(work, 0);
}

/* PREMAIN hook */
void fn_1_380(s16 mode, s16 frameNo)
{
    M562_WORK *work = lbl_1_bss_0;

    fn_1_2034(work);
    work->unk000C = 3;
    fn_1_1330(work, 0);
    lbl_1_data_0[0] = 1;
    if ((work->unk000E == 2 || work->unk000E == 3) && work->unk28A8 >= 0) {
        fn_1_9BC(work->unk28A8, 127, 1000);
    }
}

/* MAIN */
void fn_1_410(s16 mode, s16 frameNo)
{
    M562_WORK *work = lbl_1_bss_0;

    work->unk000C = 4;
    if (fn_1_1330(work, 1)) {
        MgSeqModeNext();
    }
}

/* FINISH */
void fn_1_460(s16 mode, s16 frameNo)
{
    M562_WORK *work = lbl_1_bss_0;

    if (lbl_1_data_0[0]) {
        work->player.unk088 = 0;
        switch (work->unk000E) {
        case 1:
            fn_1_1CB0(work, 0, 0);
            break;
        case 2:
            fn_1_1CB0(work, 1, 0);
            break;
        case 3:
            fn_1_1CB0(work, 2, 0);
            break;
        case 4:
            fn_1_1CB0(work, 3, 0);
            break;
        }
        if (work->unk0024) {
            MgTimerKill(work->unk0024);
            if (!work->unk0024->stopF) {
                work->unk0024->stopF = TRUE;
                work->unk0024->mode = MGTIMER_MODE_ON;
            }
            work->unk0024 = NULL;
        }
        if (work->unk000E == 4) {
            fn_1_1D9C(work);
        }
        lbl_1_data_4[0] = 1;
        lbl_1_data_0[0] = 0;
        if (work->unk000E == 3 || work->unk000E == 4) {
            fn_1_9F4(work->unk28A8, 100);
            work->unk28A8 = -1;
        }
    }
    work->unk000C = 5;
    fn_1_1330(work, 0);
}

/* PREWIN */
void fn_1_5DC(s16 mode, s16 frameNo)
{
    M562_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    if (lbl_1_data_4[0]) {
        if ((work->unk000E == 1 || work->unk000E == 2) && work->unk28A8 >= 0) {
            fn_1_9BC(work->unk28A8, 96, 1000);
        }
        lbl_1_data_4[0] = 0;
    }
    if (work->unk0022 == 0 && (work->unk000E == 3 || work->unk000E == 4)) {
        if (fn_1_1F54(work)) {
            MgSeqModeNext();
            work->unk0010 = 0;
            work->unk001C = 0;
        }
    } else {
        MgSeqModeNext();
        work->unk0010 = 0;
        work->unk001C = 0;
    }
    work->unk000C = 6;
    fn_1_1330(work, 0);
}

/* WINNER: next phase loops back to FADEIN; a loss runs evt_winner then CLOSE */
void fn_1_6DC(s16 mode, s16 frameNo)
{
    M562_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    if (work->unk0022 == 0) {
        if (work->unk000E == 4) {
            MgSeqModeNext();
        } else {
            switch (work->unk000E) {
            case 1:
                work->unk000E = 2;
                MgSeqStatBitSet(MGSEQ_STAT_FADEIN_OFF);
                break;
            case 2:
                work->unk000E = 3;
                MgSeqStatBitSet(MGSEQ_STAT_FADEIN_OFF);
                break;
            case 3:
                work->unk000E = 4;
                MgSeqStatBitReset(MGSEQ_STAT_FADEIN_OFF);
                break;
            }
            MgSeqModeSet(MGSEQ_MODE_FADEIN);
        }
    } else if (fn_1_2C118(work)) {
        MgSeqModeSet(MGSEQ_MODE_CLOSE);
    }
    work->unk000C = 7;
    fn_1_1330(work, 0);
}

/* FADEOUT */
void fn_1_7C8(s16 mode, s16 frameNo)
{
    M562_WORK *work = lbl_1_bss_0;

    fn_1_1F54(work);
    work->unk000C = 8;
    fn_1_1330(work, 0);
}

int fn_1_814(int seId)
{
    return HuAudFXPlay(seId);
}

void fn_1_83C(int seNo)
{
    HuAudFXStop(seNo);
}

void fn_1_864(int seNo, s32 speed)
{
    HuAudFXFadeOut(seNo, speed);
}

void fn_1_894(int seNo, s16 pan)
{
    HuAudFXPanning(seNo, pan);
}

void fn_1_8C4(Vec *pos, Vec *heading, float sndDist, float sndSpeed)
{
    HuAudFXListnerSet(pos, heading, sndDist, sndSpeed);
}

void fn_1_904(Vec *pos, Vec *heading)
{
    HuAudFXListnerUpdate(pos, heading);
}

int fn_1_934(int seId, Vec *pos)
{
    return HuAudFXEmiterPlay(seId, pos);
}

void fn_1_964(int seNo, Vec *pos)
{
    HuAudFXEmiterUpDate(seNo, pos);
}

int fn_1_994(s16 streamId)
{
    return HuAudSStreamPlay(streamId);
}

void fn_1_9BC(int streamNo, u8 vol, u32 speed)
{
    HuAudSStreamVolSet(streamNo, vol, speed);
}

void fn_1_9F4(int streamNo, s32 speed)
{
    HuAudSStreamFadeOut(streamNo, speed);
}

void fn_1_A24(void)
{
    HuAudAllStop();
}

int fn_1_A44(s16 streamId)
{
    return HuAudBGMPlay(streamId);
}

int fn_1_A6C(s16 streamId)
{
    return HuAudJinglePlay(streamId);
}

int fn_1_A94(s16 streamId, s16 chanNo)
{
    return HuAudSStreamChanPlay(streamId, chanNo);
}
