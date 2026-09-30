/*
 * m575dll m575.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/m575.s.
 */

#include "REL/m575dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/wipe.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* float lbl_1_rodata_10 = 10.0f; */
/* 0x18 */ /* double lbl_1_rodata_18 = 3.141592653589793; */
/* 0x20 */ /* double lbl_1_rodata_20 = 180; */
/* 0x28 */ /* float lbl_1_rodata_28 = 45.0f; */
/* 0x2C */ /* float lbl_1_rodata_2C = 20.0f; */
/* 0x30 */ /* float lbl_1_rodata_30 = 80000.0f; */
/* 0x34 */ /* float lbl_1_rodata_34 = 0.5f; */
/* 0x38 */ /* float lbl_1_rodata_38 = 0.0f; */
/* 0x3C */ /* float lbl_1_rodata_3C = 3.0f; */
/* 0x40 */ /* float lbl_1_rodata_40 = 4.0f; */
/* 0x44 */ /* s32 lbl_1_rodata_44[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x50 */ /* s32 lbl_1_rodata_50[3] = { 0xC3160000, 0x00000000, 0x00000000 }; */
/* 0x5C */ /* s32 lbl_1_rodata_5C[3] = { 0x43160000, 0x00000000, 0x00000000 }; */
/* 0x68 */ /* s32 lbl_1_rodata_68[3] = { 0xC3160000, 0x00000000, 0x00000000 }; */
/* 0x74 */ /* s32 lbl_1_rodata_74[3] = { 0x43160000, 0x00000000, 0x00000000 }; */
/* 0x80 */ /* float lbl_1_rodata_80 = 16.0f; */
/* 0x84 */ /* float lbl_1_rodata_84 = 180.0f; */
/* 0x88 */ /* float lbl_1_rodata_88 = 360.0f; */
/* 0x8C */ /* float lbl_1_rodata_8C = -180.0f; */
/* 0x90 */ /* float lbl_1_rodata_90 = 8.0f; */
/* 0x94 */ /* float lbl_1_rodata_94 = 100.0f; */
/* 0x98 */ /* float lbl_1_rodata_98 = 0.9f; */
/* 0x9C */ /* float lbl_1_rodata_9C = 0.9999999f; */
/* 0xA0 */ /* float lbl_1_rodata_A0 = 2.0f; */
/* 0xA4 */ /* float lbl_1_rodata_A4 = 1.0f; */
/* 0xA8 */ /* double lbl_1_rodata_A8 = 0.5; */
/* 0xB0 */ /* double lbl_1_rodata_B0 = 3; */
/* 0xB8 */ /* double lbl_1_rodata_B8 = 360; */
/* 0xC0 */ /* double lbl_1_rodata_C0 = 4503601774854144; */

/* --- .data --- */
/* 0x0 */ s32 lbl_1_data_0 = 1; /* set by fn_1_280, cleared by fn_1_334 */
/* 0x4 */ MGSEQ_PARAM lbl_1_data_4 = { 30, 0, fn_1_E8, fn_1_1C0, fn_1_21C, fn_1_2DC, fn_1_334, fn_1_444, fn_1_4A0, fn_1_4EC, fn_1_164 };
/* 0x2C */ s32 lbl_1_data_2C[1] = { 0 }; /* dtk folds this unreferenced zero word into lbl_1_data_4 */
/* 0x30 */ HuVecF lbl_1_data_30 = { 0.0f, 5000.0f, 10.0f }; /* shadow camera position */
/* 0x3C */ HuVecF lbl_1_data_3C = { 0.0f, 1.0f, 0.0f }; /* shadow camera up */
/* 0x48 */ HuVecF lbl_1_data_48 = { 0.0f, 0.0f, 0.0f }; /* shadow camera target */
/* 0x54 */ s32 lbl_1_data_54[1] = { 0 }; /* dtk folds this zero word into lbl_1_data_48 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x6010 */ HuVecF lbl_1_bss_6010[256][2]; /* 0x1800: debug lines */
/* 0x3C10 */ HuVecF lbl_1_bss_3C10[256][3]; /* 0x2400: debug triangles */
/* 0xC10 */ HuVecF lbl_1_bss_C10[256][4]; /* 0x3000: debug quads */
/* 0x80E */ GXColor lbl_1_bss_80E[256]; /* 0x400 (+2 dtk pad): debug line colours */
/* 0x40E */ GXColor lbl_1_bss_40E[256]; /* 0x400: debug triangle colours */
/* 0xE */ GXColor lbl_1_bss_E[256]; /* 0x400: debug quad colours */
/* 0xC */ u16 lbl_1_bss_C; /* quad count */
/* 0xA */ u16 lbl_1_bss_A; /* triangle count */
/* 0x8 */ u16 lbl_1_bss_8; /* line count */
/* 0x4 */ OMOBJMAN *lbl_1_bss_4; /* MgActorObjectSetup() */
/* 0x0 */ M575_WORK *lbl_1_bss_0; /* the work block (heap); player.c reads it */

/* --- functions (reference order) --- */
void ObjectSetup(void)
{
    lbl_1_bss_4 = MgActorObjectSetup();
    MgSeqCreate(&lbl_1_data_4);
    MgSeqModeHookAdd(MGSEQ_MODE_PREMAIN, fn_1_280);
}

void fn_1_E8(s16 mode, s16 frameNo)
{
    M575_WORK *work;

    work = lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M575_WORK), HU_MEMNUM_OVL);
    memset(lbl_1_bss_0, 0, sizeof(M575_WORK));
    fn_1_730(work, lbl_1_bss_4);
    work->unk00C = 0;
    MgSeqModeNext();
}

void fn_1_164(s16 mode, s16 frameNo)
{
    M575_WORK *work = lbl_1_bss_0;

    fn_1_C5C(work);
    HuMemDirectFree(lbl_1_bss_0);
    lbl_1_bss_0 = NULL;
    MgSeqModeNext();
}

void fn_1_1C0(s16 mode, s16 frameNo)
{
    M575_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    if (fn_1_F14(work)) {
        MgSeqModeNext();
    }
    work->unk00C = 1;
    fn_1_D08(work, 0);
}

void fn_1_21C(s16 mode, s16 frameNo)
{
    M575_WORK *work = lbl_1_bss_0;
    GAMEMESID mesId = MgSeqGameMesIdGet(); /* unused */

    if (work->unk260C < 0) {
        work->unk260C = fn_1_6B0(0x35);
    }
    work->unk00C = 2;
    fn_1_D08(work, 0);
}

void fn_1_280(s16 mode, s16 frameNo)
{
    M575_WORK *work = lbl_1_bss_0;

    fn_1_F3C(work);
    work->unk00C = 3;
    fn_1_D08(work, 0);
    lbl_1_data_0 = 1;
}

void fn_1_2DC(s16 mode, s16 frameNo)
{
    M575_WORK *work = lbl_1_bss_0;

    work->unk25D8 = 1;
    work->unk00C = 4;
    if (fn_1_D08(work, 1)) {
        MgSeqModeNext();
    }
}

void fn_1_334(s16 mode, s16 frameNo)
{
    M575_WORK *work = lbl_1_bss_0;
    s32 i;
    s32 j;
    M575_PLAYER *player;
    M575_TEAM *team;
    GAMEMESID mesId;

    if (lbl_1_data_0) {
        for (i = 0; i < 2; i++) {
            team = &work->unk018[i];
            for (j = 0; j < 2; j++) {
                player = &team->unk008[j];
                player->unk0A4 = 0;
                player->unk02C.unk00C = 0;
            }
        }
        lbl_1_data_0 = 0;
        work->unk00E = 0;
    }
    mesId = MgSeqGameMesIdGet();
    if (work->unk260C >= 0 && (GameMesStatGet(mesId) & GAMEMES_STAT_FXPLAY)) {
        fn_1_660(work->unk260C, 100);
        work->unk260C = -1;
    }
    work->unk25D8 = 0;
    work->unk00C = 5;
    fn_1_D08(work, 0);
}

void fn_1_444(s16 mode, s16 frameNo)
{
    M575_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    if (fn_1_FEC(work)) {
        MgSeqModeNext();
    }
    work->unk00C = 6;
    fn_1_D08(work, 0);
}

void fn_1_4A0(s16 mode, s16 frameNo)
{
    M575_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    MgSeqModeNext();
    work->unk00C = 7;
    fn_1_D08(work, 0);
}

void fn_1_4EC(s16 mode, s16 frameNo)
{
    M575_WORK *work = lbl_1_bss_0;

    work->unk00C = 8;
    fn_1_D08(work, 0);
}

/* retail never inlines the audio wrappers into fn_1_C5C/fn_1_FEC (m504 precedent) */
#pragma dont_inline on
int fn_1_530(int seId)
{
    return HuAudFXPlay(seId);
}

void fn_1_558(int seNo)
{
    HuAudFXStop(seNo);
}

void fn_1_580(int seNo, s32 speed)
{
    HuAudFXFadeOut(seNo, speed);
}

void fn_1_5B0(int seNo, s16 pan)
{
    HuAudFXPanning(seNo, pan);
}

void fn_1_5E0(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis)
{
    HuAudFXListnerSetEX(pos, heading, sndDist, sndSpeed, startDis, frontSurDis, backSurDis);
}

int fn_1_638(s16 streamId)
{
    return HuAudSStreamPlay(streamId);
}

void fn_1_660(int streamNo, s32 speed)
{
    HuAudSStreamFadeOut(streamNo, speed);
}

void fn_1_690(void)
{
    HuAudAllStop();
}

int fn_1_6B0(s16 streamId)
{
    return HuAudBGMPlay(streamId);
}

int fn_1_6D8(s16 streamId)
{
    return HuAudJinglePlay(streamId);
}

int fn_1_700(s16 streamId, s16 chanNo)
{
    return HuAudSStreamChanPlay(streamId, chanNo);
}
#pragma dont_inline off

void fn_1_730(M575_WORK *work, OMOBJMAN *objman)
{
    s16 n;
    s16 order[4];
    COL_ATTRPARAM param;
    float angle;
    M575_TEAM *team;
    s32 i;
    M575_PLAYER *player;
    s32 sel;

    memset(work, 0, sizeof(M575_WORK));
    work->unk000 = objman;
    work->unk010 = 1800;
    work->unk25DC = -1;
    work->unk260C = -1;
    work->unk2610 = -1;
    fn_1_3880(&work->unk018[0], 0, work);
    fn_1_3880(&work->unk018[1], 1, work);
    work->unk2600 = 0;
    work->unk25E0[work->unk2600++] = work->unk018[0].unk1A0.unk010;
    work->unk25E0[work->unk2600++] = work->unk018[1].unk1A0.unk010;
    ColKill();
    MgActorColMapInit(work->unk25E0, work->unk2600, 40);
    n = 0;
    order[0] = 1;
    order[1] = 2;
    order[2] = 3;
    order[3] = 4;
    team = &work->unk018[0];
    for (i = 0; i < 4; i++) {
        if (GwPlayerConf[i].grp == 0) {
            player = &team->unk008[n % 2];
            fn_1_535C(player, n % 2, i, team);
            order[i] = 0;
            n++;
            if (n >= 2) {
                break;
            }
        }
    }
    if (n < 2) {
        for (i = 0; i < 4; i++) {
            if (order[i] != 0) {
                player = &team->unk008[n % 2];
                fn_1_535C(player, n % 2, order[i] - 1, team);
                order[i] = 0;
                n++;
                if (n >= 2) {
                    break;
                }
            }
        }
    }
    n = 0;
    team = &work->unk018[1];
    for (i = 0; i < 4; i++) {
        if (order[i] != 0) {
            player = &team->unk008[n % 2];
            fn_1_535C(player, n % 2, order[i] - 1, team);
            n++;
        }
    }
    MgActorColMapMaskSet(0, 1);
    MgActorColMapMaskSet(1, 2);
    MgActorColMaskSet(work->unk018[0].unk008[0].unk008->actor, 1);
    MgActorColMaskSet(work->unk018[0].unk008[1].unk008->actor, 1);
    MgActorColMaskSet(work->unk018[1].unk008[0].unk008->actor, 2);
    MgActorColMaskSet(work->unk018[1].unk008[1].unk008->actor, 2);
    angle = 10.0f;
    MgActorColAttrParamGet(&param, 1);
    param.maxDot = cos(M_PI * angle / 180.0);
    MgActorColAttrParamSet(&param, 1);
    MgActorColAttrParamGet(&param, 2);
    param.maxDot = cos(M_PI * angle / 180.0);
    MgActorColAttrParamSet(&param, 2);
    Hu3DShadowMultiCreate(45.0f, 20.0f, 80000.0f, 0x11);
    Hu3DShadowMultiTPLvlSet(0.5f, -1);
    Hu3DShadowMultiSizeSet(240, -1);
    Hu3DShadowMultiPosSet(&lbl_1_data_30, &lbl_1_data_3C, &lbl_1_data_48, 0x11);
    work->unk2602 = espEntry(0x820018, 0, 0);
    espPriSet(work->unk2602, 256);
    espDispOff(work->unk2602);
    if (frand() & 1) {
        sel = 1;
    } else {
        sel = 2;
    }
    work->unk2604 = sel;
    work->unk2606[0] = frand() % 20 + 5;
    if (work->unk2604 == 2) {
        work->unk2606[1] = frand() % 10 + (work->unk2606[0] + 10);
    }
    fn_1_E478();
    fn_1_EBEC();
    Hu3DBGColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    Hu3DNoSyncSet(TRUE);
}

void fn_1_C5C(M575_WORK *work)
{
    s32 i;
    M575_TEAM *team;

    fn_1_E4C8();
    espKill(work->unk2602);
    for (i = 0; i < 2; i++) {
        team = &work->unk018[i];
        fn_1_55EC(&team->unk008[1]);
        fn_1_55EC(&team->unk008[0]);
    }
    fn_1_396C(&work->unk018[0]); /* retail: team 1 is never torn down */
    if (work->unk25DC >= 0) {
        GameMesKill(work->unk25DC);
    }
    GameMesClose();
    memset(work, 0, sizeof(M575_WORK));
    fn_1_690();
}

s32 fn_1_D08(M575_WORK *work, s32 arg1)
{
    s32 result = 0;
    HuVecF pos;
    HuVecF up;
    HuVecF target;
    HuVecF ofs;

    fn_1_39E4(&work->unk018[0]);
    fn_1_39E4(&work->unk018[1]);
    if (MgSeqModeGet() == 2 || MgSeqModeGet() == 3 || MgSeqModeGet() == 4 || MgSeqModeGet() == 5 || MgSeqModeGet() == 6
        || MgSeqModeGet() == 7 || MgSeqModeGet() == 8) {
        MgActorExec();
    }
    if (MgSeqModeGet() < 4) {
        ofs = *work->unk018[0].unk008[0].unk078;
        ofs.x = ofs.y = 0.0f;
        PSVECAdd(&lbl_1_data_30, &ofs, &pos);
        PSVECAdd(&lbl_1_data_3C, &ofs, &up);
        PSVECAdd(&lbl_1_data_48, &ofs, &target);
        Hu3DShadowMultiPosSet(&pos, &up, &target, 1);
        ofs = *work->unk018[1].unk008[0].unk078;
        ofs.x = ofs.y = 0.0f;
        PSVECAdd(&lbl_1_data_30, &ofs, &pos);
        PSVECAdd(&lbl_1_data_3C, &ofs, &up);
        PSVECAdd(&lbl_1_data_48, &ofs, &target);
        Hu3DShadowMultiPosSet(&pos, &up, &target, 0x10);
    } else if (MgSeqModeGet() == 4) {
        Hu3DShadowMultiPosSet(&lbl_1_data_30, &lbl_1_data_3C, &lbl_1_data_48, 0x11);
    }
    if (MgSeqModeGet() == 5 && work->unk010 != 0) {
        work->unk010--;
    }
    work->unk008++;
    return result;
}

s32 fn_1_F14(M575_WORK *work)
{
    return fn_1_D00C(work);
}

s32 fn_1_F3C(M575_WORK *work)
{
    s32 i;
    s32 j;
    M575_TEAM *team;
    M575_PLAYER *player;

    for (i = 0; i < 2; i++) {
        team = &work->unk018[i];
        for (j = 0; j < 2; j++) {
            player = &team->unk008[j];
            fn_1_5C88(player, 1);
            player->unk0A4 = 1;
            player->unk02C.unk00C = 1;
        }
        fn_1_3D5C(&team->unk1284, 1);
    }
    return 1;
}

s32 fn_1_FEC(M575_WORK *work)
{
    M575_TEAM *team0 = &work->unk018[0];
    M575_TEAM *team1 = &work->unk018[1];
    M575_TEN *ten0 = &team0->unk1A0;
    M575_TEN *ten1 = &team1->unk1A0;
    M575_SCORE *score0 = &team0->unk1284;
    M575_SCORE *score1 = &team1->unk1284;
    M575_PLAYER *p00 = &team0->unk008[0];
    M575_PLAYER *p01 = &team0->unk008[1];
    M575_PLAYER *p10 = &team1->unk008[0];
    M575_PLAYER *p11 = &team1->unk008[1];
    s32 result = 0;
    s32 done00;
    s32 done01;
    s32 done10;
    s32 done11;

    switch (work->unk00E) {
        case 0:
            if (ten0->unk020 < 3.0f && ten1->unk020 < 3.0f) {
                p00->unk004 = p01->unk004 = p10->unk004 = p11->unk004 = 0;
                work->unk00E++;
            }
            break;
        case 1:
            done00 = fn_1_14F0(p00);
            done01 = fn_1_14F0(p01);
            done10 = fn_1_14F0(p10);
            done11 = fn_1_14F0(p11);
            if (done00 && done01 && done10 && done11) {
                work->unk014 = 0;
                work->unk00E++;
            }
            break;
        case 2:
            if (work->unk014++ > 30) {
                work->unk014 = 0;
                work->unk00E++;
            }
            break;
        case 3:
            if (score0->unk010 != 0) {
                Hu3DMotionShiftSet(p00->unk014, p00->unk016[7], 0.0f, 4.0f, 0);
                Hu3DMotionShiftSet(p01->unk014, p01->unk016[7], 0.0f, 4.0f, 0);
                GWMgCoinSet(p00->unk00E, score0->unk010 + GWMgCoinGet(p00->unk00E));
                GWMgCoinSet(p01->unk00E, score0->unk010 + GWMgCoinGet(p01->unk00E));
            } else {
                Hu3DMotionShiftSet(p00->unk014, p00->unk016[8], 0.0f, 4.0f, 0);
                Hu3DMotionShiftSet(p01->unk014, p01->unk016[8], 0.0f, 4.0f, 0);
            }
            if (score1->unk010 != 0) {
                Hu3DMotionShiftSet(p10->unk014, p10->unk016[7], 0.0f, 4.0f, 0);
                Hu3DMotionShiftSet(p11->unk014, p11->unk016[7], 0.0f, 4.0f, 0);
                GWMgCoinSet(p10->unk00E, score1->unk010 + GWMgCoinGet(p10->unk00E));
                GWMgCoinSet(p11->unk00E, score1->unk010 + GWMgCoinGet(p11->unk00E));
            } else {
                Hu3DMotionShiftSet(p10->unk014, p10->unk016[8], 0.0f, 4.0f, 0);
                Hu3DMotionShiftSet(p11->unk014, p11->unk016[8], 0.0f, 4.0f, 0);
            }
            if (score0->unk010 + score1->unk010 != 0) {
                fn_1_6D8(0x79);
            } else {
                fn_1_6D8(0x7B);
                CharLoseVoicePlay(p00->unk010, p01->unk010, p10->unk010, p11->unk010);
            }
            work->unk014 = 0;
            work->unk00E++;
            break;
        case 4:
            if (++work->unk014 >= 209) {
                work->unk014 = 0;
                work->unk00E++;
                result = 1;
            }
            break;
    }
    return result;
}

s32 fn_1_14F0(M575_PLAYER *player)
{
    M575_TEAM *team = player->unk000;
    M575_PLAYER *partner = (&team->unk008[0] == player) ? &team->unk008[1] : &team->unk008[0];
    HuVecF target;
    HuVecF dir;
    HuVecF up = (HuVecF) { 0.0f, 1.0f, 0.0f }; /* unused */
    s32 result = 0;
    float dist;
    float angle;

    switch (player->unk004) {
        case 0:
            if (player->unk0B0 != 0 || partner->unk0B0 != 0 || player->unk008->mode != 0) {
                break;
            }
            fn_1_5C88(player, 0);
            if (&team->unk008[0] == player) {
                target = (HuVecF) { -150.0f, 0.0f, 0.0f };
            } else {
                target = (HuVecF) { 150.0f, 0.0f, 0.0f };
            }
            PSVECSubtract(&target, player->unk078, &dir);
            dir.y = 0.0f;
            dist = PSVECMag(&dir);
            if (dist > 16.0f) {
                Hu3DMotionShiftSet(player->unk014, player->unk016[1], 0.0f, 4.0f, 0x40000001);
                player->unk004 = 1;
            } else {
                if (((player->unk07C->y >= 0.0f) ? player->unk07C->y : -player->unk07C->y) > 3.0f) {
                    Hu3DMotionShiftSet(player->unk014, player->unk016[1], 0.0f, 4.0f, 0x40000001);
                }
                player->unk004 = 2;
            }
            break;
        case 1:
            if (&team->unk008[0] == player) {
                target = (HuVecF) { -150.0f, 0.0f, 0.0f };
            } else {
                target = (HuVecF) { 150.0f, 0.0f, 0.0f };
            }
            PSVECSubtract(&target, player->unk078, &dir);
            dir.y = 0.0f;
            dist = PSVECMag(&dir);
            if (dist > 16.0f) {
                PSVECNormalize(&dir, &dir);
                angle = 180.0 * (atan2(dir.x, dir.z) / M_PI);
                player->unk07C->y = fn_1_30CC(angle, player->unk07C->y, 0.5f);
                player->unk07C->y = (player->unk07C->y > 180.0f) ? player->unk07C->y - 360.0f
                    : ((player->unk07C->y <= -180.0f) ? 360.0f + player->unk07C->y : player->unk07C->y);
                PSVECScale(&dir, &dir, 8.0f);
                PSVECAdd(player->unk078, &dir, player->unk078);
                if (&team->unk008[1] == player) {
                    PSVECSubtract(player->unk078, partner->unk078, &dir);
                    dir.y = 0.0f;
                    dist = PSVECMag(&dir);
                    if (dist < 100.0f) {
                        if (dir.x || dir.z) {
                            PSVECNormalize(&dir, &dir);
                        }
                        PSVECScale(&dir, &dir, 100.0f - dist);
                        PSVECAdd(player->unk078, &dir, player->unk078);
                    }
                }
            } else {
                *player->unk078 = target;
                player->unk004++;
            }
            break;
        case 2:
            if (((player->unk07C->y >= 0.0f) ? player->unk07C->y : -player->unk07C->y) > 3.0f) {
                player->unk07C->y = fn_1_30CC(0.0f, player->unk07C->y, 0.9f);
                player->unk07C->y = (player->unk07C->y > 180.0f) ? player->unk07C->y - 360.0f
                    : ((player->unk07C->y <= -180.0f) ? 360.0f + player->unk07C->y : player->unk07C->y);
            } else {
                player->unk07C->y = 0.0f;
                Hu3DMotionShiftSet(player->unk014, player->unk016[0], 0.0f, 4.0f, 0x40000001);
                player->unk004++;
                result = 1;
            }
            break;
        case 3:
            result = 1;
            break;
    }
    return result;
}

s32 fn_1_1C00(OMOBJ *obj)
{
    return fn_1_E424(obj);
}

void fn_1_1C28(HU3DMODEL *modelP, Mtx *mtx)
{
    s32 i;

    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
    GXSetAlphaUpdate(GX_TRUE);
    for (i = 0; i < lbl_1_bss_8; i++) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 2);
        GXPosition3f32(lbl_1_bss_6010[i][0].x, lbl_1_bss_6010[i][0].y, lbl_1_bss_6010[i][0].z);
        GXColor4u8(lbl_1_bss_80E[i].r, lbl_1_bss_80E[i].g, lbl_1_bss_80E[i].b, lbl_1_bss_80E[i].a);
        GXPosition3f32(lbl_1_bss_6010[i][1].x, lbl_1_bss_6010[i][1].y, lbl_1_bss_6010[i][1].z);
        GXColor4u8(lbl_1_bss_80E[i].r, lbl_1_bss_80E[i].g, lbl_1_bss_80E[i].b, lbl_1_bss_80E[i].a);
        GXEnd();
    }
    for (i = 0; i < lbl_1_bss_A; i++) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 4);
        GXPosition3f32(lbl_1_bss_3C10[i][0].x, lbl_1_bss_3C10[i][0].y, lbl_1_bss_3C10[i][0].z);
        GXColor4u8(lbl_1_bss_40E[i].r, lbl_1_bss_40E[i].g, lbl_1_bss_40E[i].b, lbl_1_bss_40E[i].a);
        GXPosition3f32(lbl_1_bss_3C10[i][1].x, lbl_1_bss_3C10[i][1].y, lbl_1_bss_3C10[i][1].z);
        GXColor4u8(lbl_1_bss_40E[i].r, lbl_1_bss_40E[i].g, lbl_1_bss_40E[i].b, lbl_1_bss_40E[i].a);
        GXPosition3f32(lbl_1_bss_3C10[i][2].x, lbl_1_bss_3C10[i][2].y, lbl_1_bss_3C10[i][2].z);
        GXColor4u8(lbl_1_bss_40E[i].r, lbl_1_bss_40E[i].g, lbl_1_bss_40E[i].b, lbl_1_bss_40E[i].a);
        GXPosition3f32(lbl_1_bss_3C10[i][0].x, lbl_1_bss_3C10[i][0].y, lbl_1_bss_3C10[i][0].z);
        GXColor4u8(lbl_1_bss_40E[i].r, lbl_1_bss_40E[i].g, lbl_1_bss_40E[i].b, lbl_1_bss_40E[i].a);
        GXEnd();
    }
    for (i = 0; i < lbl_1_bss_C; i++) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
        GXPosition3f32(lbl_1_bss_C10[i][0].x, lbl_1_bss_C10[i][0].y, lbl_1_bss_C10[i][0].z);
        GXColor4u8(lbl_1_bss_E[i].r, lbl_1_bss_E[i].g, lbl_1_bss_E[i].b, lbl_1_bss_E[i].a);
        GXPosition3f32(lbl_1_bss_C10[i][1].x, lbl_1_bss_C10[i][1].y, lbl_1_bss_C10[i][1].z);
        GXColor4u8(lbl_1_bss_E[i].r, lbl_1_bss_E[i].g, lbl_1_bss_E[i].b, lbl_1_bss_E[i].a);
        GXPosition3f32(lbl_1_bss_C10[i][2].x, lbl_1_bss_C10[i][2].y, lbl_1_bss_C10[i][2].z);
        GXColor4u8(lbl_1_bss_E[i].r, lbl_1_bss_E[i].g, lbl_1_bss_E[i].b, lbl_1_bss_E[i].a);
        GXPosition3f32(lbl_1_bss_C10[i][3].x, lbl_1_bss_C10[i][3].y, lbl_1_bss_C10[i][3].z);
        GXColor4u8(lbl_1_bss_E[i].r, lbl_1_bss_E[i].g, lbl_1_bss_E[i].b, lbl_1_bss_E[i].a);
        GXPosition3f32(lbl_1_bss_C10[i][0].x, lbl_1_bss_C10[i][0].y, lbl_1_bss_C10[i][0].z);
        GXColor4u8(lbl_1_bss_E[i].r, lbl_1_bss_E[i].g, lbl_1_bss_E[i].b, lbl_1_bss_E[i].a);
        GXEnd();
    }
    lbl_1_bss_8 = lbl_1_bss_A = lbl_1_bss_C = 0;
}

void fn_1_2A38(HuVecF *start, HuVecF *end, GXColor *color)
{
    if (lbl_1_bss_8 < 256) {
        lbl_1_bss_6010[lbl_1_bss_8][0] = *start;
        lbl_1_bss_6010[lbl_1_bss_8][1] = *end;
        lbl_1_bss_80E[lbl_1_bss_8] = *color;
        lbl_1_bss_8++;
    }
}

void fn_1_2B10(HuVecF *p0, HuVecF *p1, HuVecF *p2, GXColor *color)
{
    if (lbl_1_bss_A < 256) {
        lbl_1_bss_3C10[lbl_1_bss_A][0] = *p0;
        lbl_1_bss_3C10[lbl_1_bss_A][1] = *p1;
        lbl_1_bss_3C10[lbl_1_bss_A][2] = *p2;
        lbl_1_bss_40E[lbl_1_bss_A] = *color;
        lbl_1_bss_A++;
    }
}

void fn_1_2C1C(HuVecF *p0, HuVecF *p1, HuVecF *p2, HuVecF *p3, GXColor *color)
{
    if (lbl_1_bss_C < 256) {
        lbl_1_bss_C10[lbl_1_bss_C][0] = *p0;
        lbl_1_bss_C10[lbl_1_bss_C][1] = *p1;
        lbl_1_bss_C10[lbl_1_bss_C][2] = *p2;
        lbl_1_bss_C10[lbl_1_bss_C][3] = *p3;
        lbl_1_bss_E[lbl_1_bss_C] = *color;
        lbl_1_bss_C++;
    }
}

void fn_1_2D5C(Quaternion *out, HuVecF *from, HuVecF *to)
{
    Quaternion q;
    HuVecF cross;
    float dot;
    float s;

    PSVECCrossProduct(from, to, &cross);
    dot = PSVECDotProduct(from, to);
    if (((dot >= 0.0f) ? dot : -dot) < 0.9999999f) {
        s = sqrtf(2.0f * (1.0f + dot));
        q.x = cross.x / s;
        q.y = cross.y / s;
        q.z = cross.z / s;
        q.w = s / 2.0f;
    } else if (dot < 0.0f) {
        q.x = 0.0f;
        q.y = 1.0f;
        q.z = 0.0f;
        q.w = 0.0f;
    } else {
        q.x = 0.0f;
        q.y = 0.0f;
        q.z = 0.0f;
        q.w = 1.0f;
    }
    *out = q;
}

float fn_1_30CC(float cur, float target, float rate)
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

void fn_1_31E8(M575_PATH *path)
{
    memset(path, 0, sizeof(M575_PATH));
}

void fn_1_3218(M575_PATH *path)
{
    memset(path, 0, sizeof(M575_PATH));
}

void fn_1_3248(M575_PATH *path, HuVecF pos, s32 time)
{
    if (path->unk000 < 20) {
        /* retail: at unk000 == 19 this adds keys 19 AND 20 -- index 20 is past every array */
        if (path->unk000 % 4 == 3) {
            path->unk004[path->unk000] = pos;
            path->unk0F4[path->unk000] = 0;
            if (path->unk000 != 0) {
                path->unk144[path->unk000] = path->unk144[path->unk000 - 1] + path->unk0F4[path->unk000 - 1];
            } else {
                path->unk144[path->unk000] = 0;
            }
            path->unk000++;
        }
        path->unk004[path->unk000] = pos;
        path->unk0F4[path->unk000] = time;
        if (path->unk000 != 0) {
            path->unk144[path->unk000] = path->unk144[path->unk000 - 1] + path->unk0F4[path->unk000 - 1];
        } else {
            path->unk144[path->unk000] = 0;
        }
        path->unk000++;
    }
}

HuVecF fn_1_33C4(M575_PATH *path, s32 time)
{
    s32 n;
    s32 i;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    float t;
    HuVecF out;

    if (path->unk000 % 4 != 0) {
        n = path->unk000;
        for (i = path->unk000 % 4; i < 4; i++) {
            path->unk004[path->unk000] = path->unk004[n - 1];
            path->unk144[path->unk000] = path->unk144[n - 1];
            path->unk0F4[path->unk000] = path->unk0F4[n - 1];
            path->unk000++;
        }
    }
    for (i = path->unk000 - 1; i >= 0; i--) {
        if (path->unk144[i] <= time) {
            a = i / 4;
            a *= 4;
            b = a + 1;
            c = b + 1;
            d = c + 1;
            break;
        }
    }
    /* retail: a..d are uninitialised when time < unk144[0] */
    t = (float)(time - path->unk144[a]) / (float)(path->unk144[d] - path->unk144[a]);
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
    out = fn_1_36E4(t, path->unk004[a], path->unk004[b], path->unk004[c], path->unk004[d]);
    return out;
}

HuVecF fn_1_36E4(float t, HuVecF p0, HuVecF p1, HuVecF p2, HuVecF p3)
{
    HuVecF out;

    out.x = fn_1_37A4(t, p0.x, p1.x, p2.x, p3.x);
    out.y = fn_1_37A4(t, p0.y, p1.y, p2.y, p3.y);
    out.z = fn_1_37A4(t, p0.z, p1.z, p2.z, p3.z);
    return out;
}

float fn_1_37A4(float t, float p0, float p1, float p2, float p3)
{
    float v;

    v = p3 * (t * (t * t)) + (p2 * ((1.0f - t) * (3.0f * t * t)) + (p0 * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + p1 * ((1.0f - t) * (3.0f * t * (1.0f - t)))));
    return v;
}

void fn_1_3880(M575_TEAM *team, s16 idx, M575_WORK *work)
{
    M575_TEN *ten = &team->unk1A0; /* unused */

    memset(team, 0, sizeof(M575_TEAM));
    team->unk000 = work;
    team->unk004 = idx;
    fn_1_9250(&team->unkE88, team);
    fn_1_851C(&team->unkE20, idx, team);
    fn_1_3DE0(&team->unk2B8, team);
    fn_1_3A7C(&team->unk1284, (idx != 0) ? 1 : 0, team);
    fn_1_4BCC(&team->unk1A0, team);
    fn_1_9BC8(&team->unkE90, team);
    fn_1_C464(&team->unk1298, team);
    fn_1_AEF0(&team->unkFDC, team);
    CharEffectLayerSet(4);
}

void fn_1_396C(M575_TEAM *team)
{
    fn_1_B074(&team->unkFDC);
    fn_1_C5E0(&team->unk1298);
    fn_1_9E8C(&team->unkE90);
    fn_1_4E98(&team->unk1A0);
    fn_1_3CD8(&team->unk1284);
    fn_1_4360(&team->unk2B8);
    fn_1_8778(&team->unkE20);
    fn_1_92C8(&team->unkE88);
    memset(team, 0, sizeof(M575_TEAM));
}

s32 fn_1_39E4(M575_TEAM *team)
{
    M575_WORK *work = team->unk000; /* unused */
    M575_TEN *ten = &team->unk1A0; /* unused */
    s32 result;

    fn_1_4EF0(&team->unk1A0);
    fn_1_562C(&team->unk008[0]);
    fn_1_562C(&team->unk008[1]);
    fn_1_3D28(&team->unk1284);
    fn_1_9EE4(&team->unkE90);
    fn_1_C630(&team->unk1298);
    fn_1_B0E8(&team->unkFDC);
    fn_1_442C(&team->unk2B8);
    fn_1_87A8(&team->unkE20);
    fn_1_931C(&team->unkE88);
    result = 0;
    return result;
}
