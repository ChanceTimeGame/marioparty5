/*
 * m510dll m510.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/m510.s.
 */

#include "REL/m510dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/gamemes.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* float lbl_1_rodata_10 = 2.0f; */
/* 0x14 */ /* float lbl_1_rodata_14 = 400.0f; */
/* 0x18 */ /* float lbl_1_rodata_18 = 100000.0f; */
/* 0x1C */ /* float lbl_1_rodata_1C = 0.5f; */
/* 0x20 */ /* u8 lbl_1_rodata_20[1] = { 0xFF }; */
/* 0x21 */ /* u8 lbl_1_rodata_21[1] = { 0x00, 0x00, 0xFF }; */
/* 0x24 */ /* u8 lbl_1_rodata_24[1] = { 0x00 }; */
/* 0x25 */ /* u8 lbl_1_rodata_25[1] = { 0x00, 0xFF, 0xFF }; */
/* 0x28 */ /* u8 lbl_1_rodata_28[1] = { 0x00 }; */
/* 0x29 */ /* u8 lbl_1_rodata_29[1] = { 0xFF, 0x00, 0xFF }; */
/* 0x2C */ /* float lbl_1_rodata_2C = 10.0f; */
/* 0x30 */ /* float lbl_1_rodata_30 = 20.0f; */
/* 0x34 */ /* float lbl_1_rodata_34 = 0.0f; */
/* 0x38 */ /* float lbl_1_rodata_38 = 0.9999999f; */
/* 0x3C */ /* float lbl_1_rodata_3C = 1.0f; */
/* 0x40 */ /* double lbl_1_rodata_40 = 0.5; */
/* 0x48 */ /* double lbl_1_rodata_48 = 3; */
/* 0x50 */ /* double lbl_1_rodata_50 = 360; */
/* 0x58 */ /* float lbl_1_rodata_58 = 360.0f; */
/* 0x5C */ /* float lbl_1_rodata_5C = 180.0f; */

/* --- .data --- */
/* 0x0 */ s32 lbl_1_data_0 = 1; /* set by fn_1_260, cleared by fn_1_30C */
/* 0x4 */ MGSEQ_PARAM lbl_1_data_4 = { 0, 0, fn_1_E8, fn_1_1C0, fn_1_21C, fn_1_2BC, fn_1_30C, fn_1_404, fn_1_494, fn_1_568, fn_1_164 }; /* .data:0x4..0x2C, seqman param */
/* 0x2C */ s32 lbl_1_data_2C[1] = { 0 }; /* dtk folds this unreferenced zero word into lbl_1_data_4; an aggregate so CW keeps it in .data */
/* 0x30 */ HuVecF lbl_1_data_30 = { 380.0f, 80000.0f, 750.0f }; /* shadow camera position */
/* 0x3C */ HuVecF lbl_1_data_3C = { 0.0f, 1.0f, 0.0f }; /* shadow camera up */
/* 0x48 */ HuVecF lbl_1_data_48 = { 380.0f, 0.0f, 950.0f }; /* shadow camera target */
/* 0x54 */ s16 lbl_1_data_54[4] = { 2, 5, 15, 8 }; /* fn_1_9B8: pitches to assign per kind */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x781C gap_05_0000781C_bss (0x4) -- dtk filler */
/* 0x7810 */ s32 lbl_1_bss_7810[3]; /* 0xC: 4-aligned, retype */
/* 0x6010 */ HuVecF lbl_1_bss_6010[256][2]; /* 0x1800: debug lines (fn_1_2148) */
/* 0x3C10 */ HuVecF lbl_1_bss_3C10[256][3]; /* 0x2400: debug triangles (fn_1_2220) */
/* 0xC10 */ HuVecF lbl_1_bss_C10[256][4]; /* 0x3000: debug quads (fn_1_2390) */
/* 0x80E */ GXColor lbl_1_bss_80E[256]; /* 0x400 (+2 dtk pad): debug line colours */
/* 0x40E */ GXColor lbl_1_bss_40E[256]; /* 0x400: debug triangle colours */
/* 0xE */ GXColor lbl_1_bss_E[256]; /* 0x400: debug quad colours */
/* 0xC */ u16 lbl_1_bss_C; /* quad count: lhz + cmplwi 0x100 */
/* 0xA */ u16 lbl_1_bss_A; /* triangle count */
/* 0x8 */ u16 lbl_1_bss_8; /* line count */
/* 0x4 */ OMOBJMAN *lbl_1_bss_4; /* MgActorObjectSetup() */
/* 0x0 */ M510_WORK *lbl_1_bss_0; /* the work block */

/* --- functions (reference order) --- */
/* 18 insns */
void ObjectSetup(void)
{
    lbl_1_bss_4 = MgActorObjectSetup();
    MgSeqCreate(&lbl_1_data_4);
    MgSeqModeHookAdd(MGSEQ_MODE_PREMAIN, fn_1_260);
}

/* 31 insns */
void fn_1_E8(s16 mode, s16 frameNo)
{
    M510_WORK *work;

    work = lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M510_WORK), HU_MEMNUM_OVL);
    memset(lbl_1_bss_0, 0, sizeof(M510_WORK));
    fn_1_7B4(work, lbl_1_bss_4);
    work->unk00C = 0;
    MgSeqModeNext();
}

/* 23 insns */
void fn_1_164(s16 mode, s16 frameNo)
{
    M510_WORK *work = lbl_1_bss_0;

    fn_1_D84(work);
    HuMemDirectFree(lbl_1_bss_0);
    lbl_1_bss_0 = NULL;
    MgSeqModeNext();
}

/* 23 insns */
void fn_1_1C0(s16 mode, s16 frameNo)
{
    M510_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    if (fn_1_1274(work)) {
        MgSeqModeNext();
    }
    work->unk00C = 1;
    fn_1_E54(work, 0);
}

/* 17 insns */
void fn_1_21C(s16 mode, s16 frameNo)
{
    M510_WORK *work = lbl_1_bss_0;

    work->unk00C = 2;
    fn_1_E54(work, 0);
}

/* 23 insns */
void fn_1_260(s16 mode, s16 frameNo)
{
    M510_WORK *work = lbl_1_bss_0;

    fn_1_129C(work);
    work->unk00C = 3;
    fn_1_E54(work, 0);
    lbl_1_data_0 = 1;
}

/* 20 insns */
void fn_1_2BC(s16 mode, s16 frameNo)
{
    M510_WORK *work = lbl_1_bss_0;

    work->unk00C = 4;
    if (fn_1_E54(work, 1)) {
        MgSeqModeNext();
    }
}

/* 62 insns */
void fn_1_30C(s16 mode, s16 frameNo)
{
    M510_WORK *work = lbl_1_bss_0;
    GAMEMESID mesId = MgSeqGameMesIdGet();
    s32 i;
    M510_PLAYER *player;
    M510_PLAYERMODEL *model;

    if (work->unk2538 >= 0 && (GameMesStatGet(mesId) & GAMEMES_STAT_FXPLAY)) {
        fn_1_6E4(work->unk2538, 100);
        work->unk2538 = -1;
    }
    if (lbl_1_data_0) {
        for (i = 0; i < 4; i++) {
            player = &work->unk01C[i];
            model = &player->unk008;
            player->unk008.unk0FC = 0;
        }
        lbl_1_data_0 = 0;
        work->unk00E = 0;
    }
    work->unk00C = 5;
    fn_1_E54(work, 0);
}

/* 36 insns */
void fn_1_404(s16 mode, s16 frameNo)
{
    M510_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    MgSeqModeChangeOff();
    if (lbl_1_bss_0->unk2534) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
        MgSeqModeNext();
    } else if (fn_1_1308(work)) {
        MgSeqModeNext();
    }
    work->unk00C = 6;
    fn_1_E54(work, 0);
}

/* 53 insns */
void fn_1_494(s16 mode, s16 frameNo)
{
    M510_WORK *work = lbl_1_bss_0;
    s32 i;
    M510_PLAYER *player;

    MgSeqModeChangeOff();
    if (lbl_1_bss_0->unk2534) {
        if (!WipeCheckEnd()) {
            for (i = 0; i < 4; i++) {
                player = &work->unk01C[i];
                GWMgScoreSet(player->unk008.unk008, player->unk850.unk024);
            }
            MgSeqModeSet(MGSEQ_MODE_CLOSE);
            return;
        }
    } else if (fn_1_1310(work)) {
        MgSeqModeNext();
    }
    work->unk00C = 7;
    fn_1_E54(work, 0);
}

/* 19 insns */
void fn_1_568(s16 mode, s16 frameNo)
{
    M510_WORK *work = lbl_1_bss_0;

    fn_1_1310(work);
    work->unk00C = 8;
    fn_1_E54(work, 0);
}

/* 10 insns */
int fn_1_5B4(int seId)
{
    return HuAudFXPlay(seId);
}

/* 10 insns */
void fn_1_5DC(int seNo)
{
    HuAudFXStop(seNo);
}

/* 12 insns */
void fn_1_604(int seNo, s32 speed)
{
    HuAudFXFadeOut(seNo, speed);
}

/* 12 insns */
void fn_1_634(int seNo, s16 pan)
{
    HuAudFXPanning(seNo, pan);
}

/* 22 insns */
void fn_1_664(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis)
{
    HuAudFXListnerSetEX(pos, heading, sndDist, sndSpeed, startDis, frontSurDis, backSurDis);
}

/* 10 insns */
int fn_1_6BC(s16 streamId)
{
    return HuAudSStreamPlay(streamId);
}

/* 12 insns */
void fn_1_6E4(int streamNo, s32 speed)
{
    HuAudSStreamFadeOut(streamNo, speed);
}

/* 8 insns */
void fn_1_714(void)
{
    HuAudAllStop();
}

/* 10 insns */
int fn_1_734(s16 streamId)
{
    return HuAudBGMPlay(streamId);
}

/* 10 insns */
int fn_1_75C(s16 streamId)
{
    return HuAudJinglePlay(streamId);
}

/* 12 insns */
int fn_1_784(s16 streamId, s16 chanNo)
{
    return HuAudSStreamChanPlay(streamId, chanNo);
}

/* 129 insns */
void fn_1_7B4(M510_WORK *work, OMOBJMAN *objman)
{
    s32 i;
    M510_PLAYER *player;

    memset(work, 0, sizeof(M510_WORK));
    work->unk000 = objman;
    work->unk010 = 1500;
    work->unk2530 = -1;
    work->unk2538 = -1;
    work->unk253C = -1;
    work->unk2534 = _CheckFlag(FLAG_INST_DECA);
    fn_1_959C(&work->unk24D8, work);
    fn_1_89B8(&work->unk2474, work);
    work->unk2508 = 30;
    fn_1_295C(&work->unk221C, work);
    for (i = 0; i < 4; i++) {
        player = &work->unk01C[i];
        fn_1_3A64(player, i, work);
    }
    work->unk252C = GWMgRecordGet(1);
    if (lbl_1_bss_0->unk2534 == 0) {
        fn_1_CE04(&work->unk24E0, 1, 0);
        work->unk24E0.unk024 = work->unk252C;
        fn_1_D354(&work->unk24E0, 1);
    }
    Hu3DShadowCreate(2.0f, 400.0f, 100000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowSizeSet(240);
    Hu3DShadowPosSet(&lbl_1_data_30, &lbl_1_data_3C, &lbl_1_data_48);
    fn_1_9B0C(work);
    for (i = 0; i < 30; i++) {
        work->unk250A[i] = 2;
    }
    fn_1_9B8(work, 0);
    fn_1_9B8(work, 1);
    fn_1_9B8(work, 3);
    work->unk2528 = 0;
    Hu3DBGColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    Hu3DNoSyncSet(TRUE);
}

/* 173 insns */
void fn_1_9B8(M510_WORK *work, s16 mode)
{
    s16 num = lbl_1_data_54[mode];
    s16 a;
    s16 b;
    s16 c;
    s32 r;

    do {
        a = frand() % 10;
        b = frand() % 10 + 10;
        c = frand() % 10 + 20;
        r = frand() % 10000;
        switch (mode) {
            case 0:
                if (num & 1) {
                    if (fn_1_C6C(work, a, 0)) {
                        work->unk250A[a] = 0;
                        num--;
                    }
                } else {
                    if (fn_1_C6C(work, c, 0)) {
                        work->unk250A[c] = 0;
                        num--;
                    }
                }
                break;
            case 1:
                if (r < 1000) {
                    if (fn_1_C6C(work, a, 1)) {
                        work->unk250A[a] = 1;
                        num--;
                    }
                } else if (r < 4000) {
                    if (fn_1_C6C(work, b, 1)) {
                        work->unk250A[b] = 1;
                        num--;
                    }
                } else {
                    if (fn_1_C6C(work, c, 1)) {
                        work->unk250A[c] = 1;
                        num--;
                    }
                }
                break;
            case 2:
                break;
            case 3:
                if (r < 1000) {
                    if (fn_1_C6C(work, a, 3)) {
                        work->unk250A[a] = 3;
                        num--;
                    }
                } else if (r < 4000) {
                    if (fn_1_C6C(work, b, 3)) {
                        work->unk250A[b] = 3;
                        num--;
                    }
                } else {
                    if (fn_1_C6C(work, c, 3)) {
                        work->unk250A[c] = 3;
                        num--;
                    }
                }
                break;
        }
    } while (num > 0);
}

/* 70 insns */
s32 fn_1_C6C(M510_WORK *work, s16 idx, s16 kind)
{
    if (idx <= 0) {
        if (kind != 2) {
            return 0;
        }
        if (work->unk250A[idx] != 2) {
            return 0;
        }
        if (work->unk250A[idx + 1] == (u8)kind) {
            return 0;
        }
    } else if (idx >= 29) {
        if (work->unk250A[idx] != 2) {
            return 0;
        }
        if (work->unk250A[idx - 1] == (u8)kind) {
            return 0;
        }
    } else {
        if (work->unk250A[idx] != 2) {
            return 0;
        }
        if (work->unk250A[idx - 1] == (u8)kind) {
            return 0;
        }
        if (work->unk250A[idx + 1] == (u8)kind) {
            return 0;
        }
    }
    return 1;
}

/* 52 insns */
void fn_1_D84(M510_WORK *work)
{
    s32 i;
    M510_PLAYER *player;

    fn_1_A454(work);
    if (lbl_1_bss_0->unk2534 == 0) {
        fn_1_D1AC(&work->unk24E0);
    }
    for (i = 0; i < 4; i++) {
        player = &work->unk01C[i];
        fn_1_3CCC(player);
    }
    fn_1_2F8C(&work->unk221C);
    fn_1_8BEC(&work->unk2474);
    fn_1_9614(&work->unk24D8);
    if (work->unk2530 >= 0) {
        GameMesKill(work->unk2530);
    }
    GameMesClose();
    memset(work, 0, sizeof(M510_WORK));
    HuAudAllStop();
}

/* 136 insns */
s32 fn_1_E54(M510_WORK *work, s32 arg1)
{
    s32 result = 0;
    u16 i;
    M510_PLAYER *player;
    M510_PITCH *pitch;
    s32 idle;
    s16 kind;

    fn_1_9668(&work->unk24D8);
    fn_1_8C1C(&work->unk2474);
    fn_1_3020(&work->unk221C);
    for (i = 0; i < 4; i++) {
        player = &work->unk01C[i];
        fn_1_3D34(player);
    }
    if (work->unk00C == 4) {
        idle = 1;
        for (i = 0; i < 4; i++) {
            player = &work->unk01C[i];
            pitch = &player->unk118;
            if (pitch->unk004 != 0) {
                idle = 0;
                break;
            }
        }
        if (work->unk2508 <= 0) {
            for (i = 0; i < 4; i++) {
                player = &work->unk01C[i];
                if (player->unk154.unk6F4 != 0) {
                    break;
                }
            }
            if (i == 4) {
                result = 1;
            }
        } else {
            if (idle) {
                kind = work->unk250A[work->unk2528++];
                for (i = 0; i < 4; i++) {
                    player = &work->unk01C[i];
                    pitch = &player->unk118;
                    pitch->unk020 = kind;
                    pitch->unk024 = 1;
                }
            }
            for (i = 0; i < 4; i++) {
                player = &work->unk01C[i];
                pitch = &player->unk118;
                if (pitch->unk004 == 3) {
                    if (work->unk2508 != 0) {
                        work->unk2508--;
                    }
                    break;
                }
            }
        }
    }
    if (lbl_1_bss_0->unk2534 == 0) {
        fn_1_D234(&work->unk24E0);
    }
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN && work->unk010 != 0) {
        work->unk010--;
    }
    work->unk008++;
    return result;
}

/* 128 insns */
void fn_1_1074(M510_WORK *work)
{
    GXColor red = { 255, 0, 0, 255 };
    GXColor blue = { 0, 0, 255, 255 };
    GXColor green = { 0, 255, 0, 255 };
    HuVecF pos;
    HuVecF start;
    HuVecF end;
    s32 step;
    M510_PLAYER *player;
    s32 i;
    M510_BALLOBJ *ball;
    M510_BALLPATH *path;
    s32 j;

    for (i = 0; i < 4; i++) {
        player = &work->unk01C[i];
        ball = &player->unk154.unk004[0];
        if (ball->unk00C == 0 || ball->unk060.unk000 == 0) {
            ball = &player->unk154.unk004[1];
        }
        if (ball->unk00C == 0) {
            continue;
        }
        path = &ball->unk060;
        if (path->unk000 != 0) {
            step = path->unk184[path->unk000 - 1] / 50;
            for (j = 0; j < 50; j++) {
                start = fn_1_C70C(path, step * j, 0.5f);
                end = fn_1_C70C(path, step * (j + 1), 0.5f);
                fn_1_2148(&start, &end, &red);
            }
            for (j = 0; j < path->unk000; j++) {
                pos = path->unk004[j];
                fn_1_2220(&pos, 10.0f, &blue);
            }
        }
        fn_1_2220(&ball->unk010, 20.0f, &green);
    }
}

/* 10 insns */
s32 fn_1_1274(M510_WORK *work)
{
    return fn_1_966C(work);
}

/* 27 insns */
s32 fn_1_129C(M510_WORK *work)
{
    s32 i;
    M510_PLAYER *player;

    for (i = 0; i < 4; i++) {
        player = &work->unk01C[i];
        fn_1_D354(&player->unk850, 1);
        player->unk008.unk0FC = 1;
    }
    return 1;
}

/* 2 insns */
s32 fn_1_1308(M510_WORK *work)
{
    return 1;
}

/* 10 insns */
s32 fn_1_1310(M510_WORK *work)
{
    return fn_1_A4F4(work);
}

/* 900 insns */
void fn_1_1338(HU3DMODEL *modelP, Mtx *mtx)
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

/* 54 insns */
void fn_1_2148(HuVecF *start, HuVecF *end, GXColor *color)
{
    if (lbl_1_bss_8 < 256) {
        lbl_1_bss_6010[lbl_1_bss_8][0] = *start;
        lbl_1_bss_6010[lbl_1_bss_8][1] = *end;
        lbl_1_bss_80E[lbl_1_bss_8] = *color;
        lbl_1_bss_8++;
    }
}

/* 92 insns */
void fn_1_2220(HuVecF *pos, float size, GXColor *color)
{
    if (lbl_1_bss_A < 256) {
        HuVecF p0;
        HuVecF p1;
        HuVecF p2;

        p0.x = pos->x;
        p0.y = pos->y;
        p0.z = pos->z - size;
        p1.x = pos->x + size;
        p1.y = pos->y;
        p1.z = pos->z + size;
        p2.x = pos->x - size;
        p2.y = pos->y;
        p2.z = pos->z + size;
        lbl_1_bss_3C10[lbl_1_bss_A][0] = p0;
        lbl_1_bss_3C10[lbl_1_bss_A][1] = p1;
        lbl_1_bss_3C10[lbl_1_bss_A][2] = p2;
        lbl_1_bss_40E[lbl_1_bss_A] = *color;
        lbl_1_bss_A++;
    }
}

/* 80 insns */
void fn_1_2390(HuVecF *p0, HuVecF *p1, HuVecF *p2, HuVecF *p3, GXColor *color)
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

/* 220 insns */
void fn_1_24D0(Quaternion *out, HuVecF *from, HuVecF *to)
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

/* 71 insns */
float fn_1_2840(float cur, float target, float rate)
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

