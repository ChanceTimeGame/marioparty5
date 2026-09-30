/*
 * m504dll m504.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m504dll/asm/REL/m504dll/m504.s.
 */

#include "REL/m504dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/esprite.h"
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
/* 0x10 */ /* float lbl_1_rodata_10 = 576.0f; */
/* 0x14 */ /* float lbl_1_rodata_14 = 240.0f; */
/* 0x18 */ /* float lbl_1_rodata_18 = 20.0f; */
/* 0x1C */ /* float lbl_1_rodata_1C = 30000.0f; */
/* 0x20 */ /* float lbl_1_rodata_20 = 0.5f; */
/* 0x24 */ /* float lbl_1_rodata_24 = 56.0f; */
/* 0x28 */ /* float lbl_1_rodata_28[2] = { 24.0f, 0.0f }; */

/* --- .data --- */
/* 0x0 */ MGSEQ_PARAM lbl_1_data_0 = { 300, 0, fn_1_114, fn_1_1EC, fn_1_25C, fn_1_298, fn_1_2F0, fn_1_37C, fn_1_460, fn_1_59C, fn_1_190 };
/* 0x28 */ s32 lbl_1_data_28[1] = { 0x00000001 };
/* 0x2C */ s32 lbl_1_data_2C[19] = { 0x003E0000, 0x003E0001, 0x003E0002, 0x003E0003, 0x003E0004, 0x003E0005, 0x003E0006, 0x003E0007, 0x003E0008, 0x003E0009, 0x003E000A, 0x003E000B, 0x003E000C, 0x003E000D, 0x003E000E, 0x003E000F, 0x003E0010, 0x003E0011, 0x003E0012 }; /* data nums */
/* 0x78 */ HuVecF lbl_1_data_78[4] = { { 16.0f, 4e+01f, 0.0f }, { 464.0f, 4e+01f, 0.0f }, { 16.0f, 408.0f, 0.0f }, { 464.0f, 408.0f, 0.0f } };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x6010 */ HuVecF lbl_1_bss_6010[256][2]; /* 0x1800: debug lines */
/* 0x3C10 */ HuVecF lbl_1_bss_3C10[256][3]; /* 0x2400: debug triangles */
/* 0xC10 */ HuVecF lbl_1_bss_C10[256][4]; /* 0x3000: debug quads */
/* 0x80E */ GXColor lbl_1_bss_80E[256]; /* 0x400 (+2 dtk pad): debug line colours */
/* 0x40E */ GXColor lbl_1_bss_40E[256]; /* 0x400: debug triangle colours */
/* 0xE */ GXColor lbl_1_bss_E[256]; /* 0x400: debug quad colours */
/* 0xC */ u16 lbl_1_bss_C; /* quad count: lhz */
/* 0xA */ u16 lbl_1_bss_A; /* triangle count: lhz */
/* 0x8 */ u16 lbl_1_bss_8; /* line count: lhz */
/* 0x4 */ OMOBJMAN *lbl_1_bss_4; /* omInitObjMan(0x200, 0x2000) in ObjectSetup */
/* 0x0 */ M504_WORK *lbl_1_bss_0; /* the work block; player.c reads it */

/* --- functions (reference order) --- */
/* 29 insns */
void ObjectSetup(void)
{
    lbl_1_bss_4 = omInitObjMan(0x200, 0x2000);
    omGameSysInit(lbl_1_bss_4);
    if (_CheckFlag(FLAG_INST_DECA)) {
        lbl_1_data_0.maxTime = 0;
    }
    MgSeqCreate(&lbl_1_data_0);
}

/* 31 insns */
void fn_1_114(s16 mode, s16 frameNo)
{
    M504_WORK *work;

    work = lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M504_WORK), HU_MEMNUM_OVL);
    memset(lbl_1_bss_0, 0, sizeof(M504_WORK));
    fn_1_7EC(work, lbl_1_bss_4);
    work->unk1214 = -1;
    MgSeqModeNext();
}

/* 23 insns */
void fn_1_190(s16 mode, s16 frameNo)
{
    M504_WORK *work = lbl_1_bss_0;

    fn_1_9F0(work);
    HuMemDirectFree(lbl_1_bss_0);
    lbl_1_bss_0 = NULL;
    MgSeqModeNext();
}

/* 28 insns */
void fn_1_1EC(s16 mode, s16 frameNo)
{
    M504_WORK *work = lbl_1_bss_0;

    MgSeqModeChangeOff();
    if (fn_1_F34(work)) {
        if (work->unk1234 >= 0) {
            fn_1_614(work->unk1234);
            work->unk1234 = -1;
        }
        MgSeqModeNext();
    }
    fn_1_C64(work, 0);
}

/* 15 insns */
void fn_1_25C(s16 mode, s16 frameNo)
{
    M504_WORK *work = lbl_1_bss_0;

    fn_1_C64(work, 0);
}

/* 22 insns */
void fn_1_298(s16 mode, s16 frameNo)
{
    M504_WORK *work = lbl_1_bss_0;

    work->unk1210 = 1;
    if (fn_1_C64(work, 1)) {
        work->unk1210 = 0;
        MgSeqModeNext();
    }
}

/* 35 insns */
void fn_1_2F0(s16 mode, s16 frameNo)
{
    M504_WORK *work = lbl_1_bss_0;
    GAMEMESID mesId;

    work->unk1210 = 0;
    mesId = MgSeqGameMesIdGet();
    if (work->unk1230 >= 0 && (GameMesStatGet(mesId) & GAMEMES_STAT_FXPLAY)) {
        fn_1_71C(work->unk1230, 100);
        work->unk1230 = -1;
    }
    fn_1_C64(work, 0);
}

/* 57 insns */
void fn_1_37C(s16 mode, s16 frameNo)
{
    M504_WORK *work = lbl_1_bss_0;
    s32 i;
    M504_LANE *lane;
    s32 done;

    MgSeqModeChangeOff();
    if (lbl_1_bss_0->unk122C) {
        done = 1;
        for (i = 0; i < 4; i++) {
            lane = &work->unk040[i];
            if (lane->unk008.unk006 == 2 || lane->unk008.unk006 == 3) {
                done = 0;
            }
        }
        if (done) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
            MgSeqModeNext();
        }
    } else if (fn_1_10C4(work)) {
        MgSeqModeNext();
    }
    fn_1_C64(work, 0);
}

/* 79 insns */
void fn_1_460(s16 mode, s16 frameNo)
{
    M504_WORK *work = lbl_1_bss_0;
    s32 i;
    M504_LANE *lane;
    s32 time;

    MgSeqModeChangeOff();
    if (lbl_1_bss_0->unk122C) {
        if (!WipeCheckEnd()) {
            for (i = 0; i < 4; i++) {
                lane = &work->unk040[i];
                time = MgTimerValueGet(lane->unk470);
                if (lane->unk008.unk0D0) {
                    GWMgScoreSet(lane->unk008.unk00C, time);
                } else {
                    GWMgScoreSet(lane->unk008.unk00C, 0);
                }
            }
            MgSeqModeSet(MGSEQ_MODE_CLOSE);
            return;
        }
    } else if (fn_1_1080(work)) {
        if (work->unk1214 >= 0) {
            /* the coin payout: 10 coins to the winning lane's player, practice-guarded (inline) */
            GWMgCoinBonusSet(work->unk1214, 10);
        }
        MgSeqModeNext();
    }
    fn_1_C64(work, 0);
}

/* 20 insns */
void fn_1_59C(s16 mode, s16 frameNo)
{
    M504_WORK *work = lbl_1_bss_0;

    if (work->unk1214 >= 0) {
        fn_1_1080(work);
    }
    fn_1_C64(work, 0);
}

/* audio wrappers: = m502 fn_1_198 .. fn_1_368 / m565 fn_1_C18 .. fn_1_E18 (no HuAudFXVolSet) */
/* retail never inlines them into fn_1_9F0/fn_1_10C4 below (m502 precedent) */
#pragma dont_inline on
/* 10 insns */
int fn_1_5EC(int seId)
{
    return HuAudFXPlay(seId);
}

/* 10 insns */
void fn_1_614(int seNo)
{
    HuAudFXStop(seNo);
}

/* 12 insns */
void fn_1_63C(int seNo, s32 speed)
{
    HuAudFXFadeOut(seNo, speed);
}

/* 12 insns */
void fn_1_66C(int seNo, s16 pan)
{
    HuAudFXPanning(seNo, pan);
}

/* 22 insns */
void fn_1_69C(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis)
{
    HuAudFXListnerSetEX(pos, heading, sndDist, sndSpeed, startDis, frontSurDis, backSurDis);
}

/* 10 insns */
int fn_1_6F4(s16 streamId)
{
    return HuAudSStreamPlay(streamId);
}

/* 12 insns */
void fn_1_71C(int streamNo, s32 speed)
{
    HuAudSStreamFadeOut(streamNo, speed);
}

/* 8 insns */
void fn_1_74C(void)
{
    HuAudAllStop();
}

/* 10 insns */
int fn_1_76C(s16 streamId)
{
    return HuAudBGMPlay(streamId);
}

/* 10 insns */
int fn_1_794(s16 streamId)
{
    return HuAudJinglePlay(streamId);
}

/* 12 insns */
int fn_1_7BC(s16 streamId, s16 chanNo)
{
    return HuAudSStreamChanPlay(streamId, chanNo);
}
#pragma dont_inline off

/* 129 insns */
void fn_1_7EC(M504_WORK *work, OMOBJMAN *objman)
{
    u16 i;

    memset(work, 0, sizeof(M504_WORK));
    work->unk000 = objman;
    work->unk00C = 10800;
    work->unk122C = _CheckFlag(FLAG_INST_DECA);
    work->unk1220 = -1;
    work->unk1230 = -1;
    work->unk1234 = -1;
    work->unk121C = espEntry(DATANUM(DATA_m504, 0x4A), 10, 0);
    espDispOff(work->unk121C);
    espDrawNoSet(work->unk121C, 0);
    espPosSet(work->unk121C, 576.0f, 240.0f);
    espAttrSet(work->unk121C, 1);
    work->unk121E = espEntry(DATANUM(DATA_m504, 0x4B), 10, 0);
    espDispOff(work->unk121E);
    espDrawNoSet(work->unk121E, 0);
    espPosSet(work->unk121E, 576.0f, 240.0f);
    espAttrSet(work->unk121E, 1);
    fn_1_AA8(work);
    /* retail bug (0x90C): fn_1_D03C is called without its work argument, so light->unk000
     * is whatever r4 holds (nothing reads it). The host must pass something. */
    fn_1_D03C(&work->unk038);
    for (i = 0; i < 4; i++) {
        fn_1_23DC(&work->unk040[i], i, work);
    }
    Hu3DShadowMultiCreate(20.0f, 20.0f, 30000.0f, 15);
    Hu3DShadowMultiTPLvlSet(0.5f, -1);
    Hu3DShadowMultiSizeSet(192, -1);
    fn_1_D10C();
    fn_1_DA68();
    work->unk1214 = -1;
    lbl_1_data_28[0] = 1;
    Hu3DBGColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    Hu3DNoSyncSet(TRUE);
}

/* 46 insns */
void fn_1_9F0(M504_WORK *work)
{
    u16 i;

    fn_1_128E0(work);
    fn_1_D15C();
    for (i = 0; i < 4; i++) {
        fn_1_24A0(&work->unk040[i]);
    }
    fn_1_D0B4(&work->unk038);
    fn_1_AF0(work);
    if (work->unk1220 >= 0) {
        GameMesKill(work->unk1220);
    }
    GameMesClose();
    espKill(work->unk121C);
    espKill(work->unk121E);
    memset(work, 0, sizeof(M504_WORK));
    fn_1_74C();
}

/* 18 insns */
void fn_1_AA8(M504_WORK *work)
{
    s16 *modelId = work->unk012;

    memset(modelId, 0, sizeof(work->unk012));
    fn_1_B38(modelId);
}

/* 18 insns */
void fn_1_AF0(M504_WORK *work)
{
    s16 *modelId = work->unk012;

    fn_1_C08(modelId);
    memset(modelId, 0, sizeof(work->unk012));
}

/* 52 insns */
void fn_1_B38(s16 *modelId)
{
    s32 i;
    HU3DMODELID model;

    for (i = 0; i < 19; i++) {
        model = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2C[i], HU_MEMNUM_OVL, HEAP_MODEL));
        modelId[i] = model;
        switch (lbl_1_data_2C[i]) {
            case DATANUM(DATA_m504, 0x07):
            case DATANUM(DATA_m504, 0x0C):
                Hu3DModelShadowMapSet(model);
                break;
        }
        Hu3DModelAttrSet(modelId[i], HU3D_ATTR_DISPOFF);
    }
}

/* 23 insns */
void fn_1_C08(s16 *modelId)
{
    s32 i;

    for (i = 0; i < 19; i++) {
        Hu3DModelKill(modelId[i]);
        modelId[i] = 0;
    }
}

/* 180 insns */
s32 fn_1_C64(M504_WORK *work, s32 arg1)
{
    u16 i;
    M504_LANE *lane;
    s32 result;
    s32 allStopped;

    if (MgSeqModeGet() >= MGSEQ_MODE_MAIN && lbl_1_data_28[0]) {
        if (lbl_1_bss_0->unk122C) {
            for (i = 0; i < 4; i++) {
                lane = &work->unk040[i];
                MgTimerParamSet(lane->unk470, 0, 5400, 0);
                MgTimerModeOnSet(lane->unk470, 2);
            }
        }
        lbl_1_data_28[0] = 0;
    }
    result = 0;
    if (!lbl_1_bss_0->unk122C) {
        for (i = 0; i < 4; i++) {
            lane = &work->unk040[i];
            if (fn_1_24F8(lane)) {
                result = 1;
                if (arg1) {
                    work->unk1214 = i;
                    work->unk1210 = 0;
                    break;
                }
            }
            if (work->unk1210) {
                lane->unk008.unk0C4 = 1;
                lane->unk0DC.unk07C = 1;
            } else {
                lane->unk008.unk0C4 = 0;
                lane->unk0DC.unk07C = 0;
            }
        }
    } else {
        allStopped = 1;
        for (i = 0; i < 4; i++) {
            lane = &work->unk040[i];
            if (work->unk1210) {
                if (!lane->unk008.unk0D0) {
                    lane->unk008.unk0C4 = 1;
                    lane->unk0DC.unk07C = 1;
                }
            } else {
                lane->unk008.unk0C4 = 0;
                lane->unk0DC.unk07C = 0;
            }
            if (fn_1_24F8(lane) && MgSeqModeGet() >= MGSEQ_MODE_MAIN) {
                lane->unk008.unk0C4 = 0;
                lane->unk0DC.unk07C = 0;
                if (MgTimerModeGet(lane->unk470)) {
                    if (!lane->unk470->stopF) {
                        lane->unk470->stopF = 1;
                        lane->unk470->mode = 1;
                    }
                    lane->unk008.unk0D0 = 1;
                }
            }
            if (MgSeqModeGet() >= MGSEQ_MODE_MAIN && MgTimerModeGet(lane->unk470)) {
                allStopped = 0;
            }
        }
        if (MgSeqModeGet() >= MGSEQ_MODE_MAIN && allStopped) {
            for (i = 0; i < 4; i++) {
                lane = &work->unk040[i];
                lane->unk008.unk0C4 = 0;
                lane->unk0DC.unk07C = 0;
            }
            result = 1;
        }
    }
    if (work->unk00C) {
        work->unk00C--;
    }
    return result;
}

/* 83 insns */
s32 fn_1_F34(M504_WORK *work)
{
    s32 result = 0;
    u16 i;
    M504_LANE *lane;

    if (fn_1_E14C(work)) {
        for (i = 0; i < 4; i++) {
            lane = &work->unk040[i];
            Hu3DModelAttrSet(lane->unk15C.unk00E, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lane->unk008.unk0C8, HU3D_ATTR_ZCMP_OFF);
            if (lbl_1_bss_0->unk122C) {
                lane->unk470 = MgTimerCreate(2);
                MgTimerPosSet(lane->unk470, 56.0f + lbl_1_data_78[i].x, 24.0f + lbl_1_data_78[i].y);
                MgTimerDigitColorSet(lane->unk470, 255, 255, 255);
                MgTimerParamSet(lane->unk470, 0, 0, 0);
                MgTimerModeOnSet(lane->unk470, 0);
            }
        }
        result = 1;
    }
    return result;
}

/* 17 insns */
s32 fn_1_1080(M504_WORK *work)
{
    s32 result = 0;

    if (fn_1_118E8(work)) {
        result = 1;
    }
    return result;
}

/* 121 insns */
s32 fn_1_10C4(M504_WORK *work)
{
    s32 i;

    if (work->unk1214 >= 0) {
        return 1;
    }
    for (i = 0; i < 4; i++) {
        if (work->unk040[i].unk0DC.unk004 < 5) {
            return 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (work->unk040[i].unk008.unk006 == 2 || work->unk040[i].unk008.unk006 == 3) {
            return 0;
        }
    }
    if (work->unk1220 < 0) {
        work->unk1220 = GameMesMgDrawCreate();
        work->unk1210 = 0;
        work->unk010 = 0;
        for (i = 0; i < 4; i++) {
            work->unk040[i].unk008.unk08C = 1;
            work->unk040[i].unk0DC.unk024 = 1;
        }
    } else {
        if (work->unk1230 < 0) {
            work->unk1230 = fn_1_794(123);
        }
        if (work->unk010 == 0) {
            CharLoseVoicePlay(work->unk040[0].unk008.unk010, work->unk040[1].unk008.unk010, work->unk040[2].unk008.unk010, work->unk040[3].unk008.unk010);
        }
        if (++work->unk010 >= 210) {
            MgSeqModeSet(MGSEQ_MODE_FADEOUT);
            work->unk1220 = -1;
            for (i = 0; i < 4; i++) {
                if (work->unk040[i].unk15C.unk05C >= 0) {
                    fn_1_63C(work->unk040[i].unk15C.unk05C, 1000);
                    work->unk040[i].unk15C.unk05C = -1;
                }
            }
        }
    }
    return 0;
}

/* 900 insns; = m510 fn_1_1338 */
void fn_1_12A8(HU3DMODEL *modelP, Mtx *mtx)
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

/* 54 insns; = m510 fn_1_2148 */
void fn_1_20B8(HuVecF *start, HuVecF *end, GXColor *color)
{
    if (lbl_1_bss_8 < 256) {
        lbl_1_bss_6010[lbl_1_bss_8][0] = *start;
        lbl_1_bss_6010[lbl_1_bss_8][1] = *end;
        lbl_1_bss_80E[lbl_1_bss_8] = *color;
        lbl_1_bss_8++;
    }
}

/* 67 insns; = m565 main.c fn_1_1FF8 */
void fn_1_2190(HuVecF *p0, HuVecF *p1, HuVecF *p2, GXColor *color)
{
    if (lbl_1_bss_A < 256) {
        lbl_1_bss_3C10[lbl_1_bss_A][0] = *p0;
        lbl_1_bss_3C10[lbl_1_bss_A][1] = *p1;
        lbl_1_bss_3C10[lbl_1_bss_A][2] = *p2;
        lbl_1_bss_40E[lbl_1_bss_A] = *color;
        lbl_1_bss_A++;
    }
}

/* 80 insns; = m510 fn_1_2390 */
void fn_1_229C(HuVecF *p0, HuVecF *p1, HuVecF *p2, HuVecF *p3, GXColor *color)
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
