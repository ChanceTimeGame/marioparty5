/*
 * m565dll main.c -- written 2026-09-23 (W1 forks; see NOTES.md). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m565dll/asm/REL/m565dll/main.s.
 */

#include "REL/m565dll.h"

#include "game/audio.h"
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
/* 0x78 */ /* float lbl_1_rodata_78 = 20.0f; */
/* 0x7C */ /* float lbl_1_rodata_7C = 30000.0f; */
/* 0x80 */ /* float lbl_1_rodata_80 = 0.5f; */
/* 0x84 */ /* float lbl_1_rodata_84 = 0.0f; */
/* 0x88 */ /* float lbl_1_rodata_88 = 0.9999999f; */
/* 0x8C */ /* float lbl_1_rodata_8C = 2.0f; */
/* 0x90 */ /* float lbl_1_rodata_90 = 1.0f; */
/* 0x98 */ /* double lbl_1_rodata_98 = 0.5; */
/* 0xA0 */ /* double lbl_1_rodata_A0 = 3; */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x6010 */ HuVecF lbl_1_bss_6010[256][2]; /* 0x1800: debug lines (m510 fn_1_2148 twin) */
/* 0x3C10 */ HuVecF lbl_1_bss_3C10[256][3]; /* 0x2400: debug triangles */
/* 0xC10 */ HuVecF lbl_1_bss_C10[256][4]; /* 0x3000: debug quads */
/* 0x80E */ GXColor lbl_1_bss_80E[256]; /* 0x400 (+2 dtk pad): debug line colours */
/* 0x40E */ GXColor lbl_1_bss_40E[256]; /* 0x400: debug triangle colours */
/* 0xE */ GXColor lbl_1_bss_E[256]; /* 0x400: debug quad colours */
/* 0xC */ u16 lbl_1_bss_C; /* quad count: lhz */
/* 0xA */ u16 lbl_1_bss_A; /* triangle count: lhz */
/* 0x8 */ u16 lbl_1_bss_8; /* line count: lhz */

/* --- functions (reference order) --- */
/* 64 insns; m510 fn_1_7B4 */
void fn_1_E48(M565_WORK *work, OMOBJMAN *objman)
{
    memset(work, 0, sizeof(M565_WORK));
    work->unk000 = objman;
    work->unk010 = 3600;
    work->unk3874 = -1;
    work->unk3878 = -1;
    work->unk387C = -1;
    fn_1_25B4(&work->unk018, work);
    Hu3DShadowCreate(20.0f, 20.0f, 30000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowSizeSet(240);
    Hu3DShadowPosSet(&lbl_1_data_30, &lbl_1_data_3C, &lbl_1_data_48);
    Hu3DBGColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    Hu3DNoSyncSet(TRUE);
    Hu3DHookFuncCreate(fn_1_1110);
}

/* 24 insns; m510 fn_1_D84 */
void fn_1_F48(M565_WORK *work)
{
    fn_1_2A94(&work->unk018);
    if (work->unk3874 >= 0) {
        GameMesKill(work->unk3874);
    }
    GameMesClose();
    memset(work, 0, sizeof(M565_WORK));
    fn_1_DA8();
}

/* 41 insns; m510 fn_1_E54 */
s32 fn_1_FA8(M565_WORK *work, s32 arg1)
{
    s32 result = 0;

    if (fn_1_2B20(&work->unk018)) {
        result = 1;
    }
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN || MgSeqModeGet() == MGSEQ_MODE_FINISH || MgSeqModeGet() == MGSEQ_MODE_PREWIN
        || MgSeqModeGet() == MGSEQ_MODE_WINNER) {
        MgActorExec();
    }
    if (work->unk010 != 0) {
        work->unk010--;
    }
    work->unk008++;
    return result;
}

/* 10 insns */
s32 fn_1_104C(M565_WORK *work)
{
    return fn_1_E740(work);
}

/* 27 insns */
s32 fn_1_1074(M565_WORK *work)
{
    s32 i;
    M565_PLAYER *player;

    for (i = 0; i < 4; i++) {
        player = &work->unk018.unk008[i];
        fn_1_8984(player, 1);
        player->unk094 = 1;
    }
    return 1;
}

/* 10 insns */
s32 fn_1_10E0(M565_WORK *work)
{
    return fn_1_EE4C(work);
}

/* 2 insns */
s32 fn_1_1108(M565_WORK *work)
{
    return 0;
}

/* 900 insns; = m510 fn_1_1338 */
void fn_1_1110(HU3DMODEL *modelP, Mtx *mtx)
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
void fn_1_1F20(HuVecF *start, HuVecF *end, GXColor *color)
{
    if (lbl_1_bss_8 < 256) {
        lbl_1_bss_6010[lbl_1_bss_8][0] = *start;
        lbl_1_bss_6010[lbl_1_bss_8][1] = *end;
        lbl_1_bss_80E[lbl_1_bss_8] = *color;
        lbl_1_bss_8++;
    }
}

/* 67 insns: debug triangle from three points (m510 fn_1_2220 takes a centre + size) */
void fn_1_1FF8(HuVecF *p0, HuVecF *p1, HuVecF *p2, GXColor *color)
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
void fn_1_2104(HuVecF *p0, HuVecF *p1, HuVecF *p2, HuVecF *p3, GXColor *color)
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

/* 220 insns; = m510 fn_1_24D0 */
void fn_1_2244(Quaternion *out, HuVecF *from, HuVecF *to)
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
