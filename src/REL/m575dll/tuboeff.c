/*
 * m575dll tuboeff.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/tuboeff.s.
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
/* 0x3D8 */ /* s32 lbl_1_rodata_3D8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x3E4 */ /* s32 lbl_1_rodata_3E4[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x3F0 */ /* s32 lbl_1_rodata_3F0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x3FC */ /* s32 lbl_1_rodata_3FC[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x408 */ /* s32 lbl_1_rodata_408[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x414 */ /* float lbl_1_rodata_414 = 0.25f; */
/* 0x418 */ /* float lbl_1_rodata_418 = 12.0f; */
/* 0x41C */ /* float lbl_1_rodata_41C = 0.5f; */
/* 0x420 */ /* float lbl_1_rodata_420 = 1.0f; */
/* 0x424 */ /* float lbl_1_rodata_424 = -1.0f; */
/* 0x428 */ /* s32 lbl_1_rodata_428[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x434 */ /* s32 lbl_1_rodata_434[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x440 */ /* float lbl_1_rodata_440 = 16.666666f; */
/* 0x444 */ /* float lbl_1_rodata_444 = 0.0f; */
/* 0x448 */ /* float lbl_1_rodata_448[2] = { 0.9999f, 0.0f }; */

/* --- functions (reference order) --- */

/* 246 insns */
void fn_1_9320(M575_TUBOEFF *eff, u16 shape, float mass, float w, float h)
{
    Vec size;
    memset(eff, 0, sizeof(M575_TUBOEFF));
    eff->unk008 = mass;
    eff->unk004 = shape;
    switch (shape) {
    case 0:
        eff->unk00C = eff->unk008 * (w * w) / 4.0f + eff->unk008 * (h * h) / 12.0f;
        eff->unk010 = eff->unk008 * (w * w) / 2.0f;
        eff->unk014 = eff->unk008 * (w * w) / 4.0f + eff->unk008 * (h * h) / 12.0f;
        break;
    default:
        size.x = size.y = size.z = w;
        eff->unk00C = size.y * (size.z * (eff->unk008 * size.x)) * (size.y * size.y + size.x * size.x) / 12.0f;
        eff->unk010 = size.y * (size.z * (eff->unk008 * size.x)) * (size.x * size.x + size.z * size.z) / 12.0f;
        eff->unk014 = size.y * (size.z * (eff->unk008 * size.x)) * (size.y * size.y + size.z * size.z) / 12.0f;
        break;
    }
    eff->unk0E4 = w;
    eff->unk0E8 = h;
    PSMTXIdentity(eff->unk018);
    eff->unk018[0][0] = 1.0f / eff->unk00C;
    eff->unk018[1][1] = 1.0f / eff->unk010;
    eff->unk018[2][2] = 1.0f / eff->unk014;
    PSMTXIdentity(eff->unk048);
    eff->unk048[0][0] = -1.0f;
    eff->unk048[2][2] = -1.0f;
    {
        Vec zero = { 0.0f, 0.0f, 0.0f };
        Vec *src = &zero;
        eff->unk0A8 = *src;
    }
    {
        Vec zero = { 0.0f, 0.0f, 0.0f };
        Vec *src = &zero;
        eff->unk0B4 = *src;
    }
    {
        Vec zero = { 0.0f, 0.0f, 0.0f };
        Vec *src = &zero;
        eff->unk0CC = *src;
    }
    {
        Vec zero = { 0.0f, 0.0f, 0.0f };
        Vec *src = &zero;
        eff->unk0D8 = *src;
    }
    {
        Vec zero = { 0.0f, 0.0f, 0.0f };
        Vec *src = &zero;
        eff->unk0C0 = *src;
    }
}

/* 12 insns */
void fn_1_96F8(M575_TUBOEFF *eff)
{
    memset(eff, 0, sizeof(M575_TUBOEFF));
}

/* 268 insns */
void fn_1_9728(M575_TUBOEFF *eff)
{
    Mtx inertia;
    Mtx skew;
    Mtx dRot;
    Mtx rotT;
    Vec vel;
    Vec omega;
    PSMTXTranspose(eff->unk048, rotT);
    PSMTXConcat(eff->unk048, eff->unk018, inertia);
    PSMTXConcat(inertia, rotT, inertia);
    PSMTXMultVec(inertia, &eff->unk0B4, &omega);
    PSVECScale(&eff->unk0A8, &vel, 1.0f / eff->unk008);
    eff->unk0C0.x += 16.666666f * vel.x;
    eff->unk0C0.y += 16.666666f * vel.y;
    eff->unk0C0.z += 16.666666f * vel.z;
    eff->unk0A8.x += 16.666666f * eff->unk0CC.x;
    eff->unk0A8.y += 16.666666f * eff->unk0CC.y;
    eff->unk0A8.z += 16.666666f * eff->unk0CC.z;
    eff->unk0B4.x += 16.666666f * eff->unk0D8.x;
    eff->unk0B4.y += 16.666666f * eff->unk0D8.y;
    eff->unk0B4.z += 16.666666f * eff->unk0D8.z;
    PSMTXIdentity(skew);
    skew[0][0] = 0.0f;
    skew[0][1] = -omega.z;
    skew[0][2] = omega.y;
    skew[1][0] = omega.z;
    skew[1][1] = 0.0f;
    skew[1][2] = -omega.x;
    skew[2][0] = -omega.y;
    skew[2][1] = omega.x;
    skew[2][2] = 0.0f;
    PSMTXConcat(skew, eff->unk048, dRot);
    eff->unk048[0][0] += 16.666666f * dRot[0][0];
    eff->unk048[0][1] += 16.666666f * dRot[0][1];
    eff->unk048[0][2] += 16.666666f * dRot[0][2];
    eff->unk048[1][0] += 16.666666f * dRot[1][0];
    eff->unk048[1][1] += 16.666666f * dRot[1][1];
    eff->unk048[1][2] += 16.666666f * dRot[1][2];
    eff->unk048[2][0] += 16.666666f * dRot[2][0];
    eff->unk048[2][1] += 16.666666f * dRot[2][1];
    eff->unk048[2][2] += 16.666666f * dRot[2][2];
    PSVECNormalize((Vec *)eff->unk048[0], (Vec *)eff->unk048[0]);
    PSVECNormalize((Vec *)eff->unk048[1], (Vec *)eff->unk048[1]);
    PSVECNormalize((Vec *)eff->unk048[2], (Vec *)eff->unk048[2]);
    PSMTXInverse(eff->unk048, eff->unk078);
    {
        Vec zero = { 0.0f, 0.0f, 0.0f };
        Vec *src = &zero;
        eff->unk0CC = *src;
    }
    {
        Vec zero = { 0.0f, 0.0f, 0.0f };
        Vec *src = &zero;
        eff->unk0D8 = *src;
    }
    PSVECScale(&eff->unk0A8, &eff->unk0A8, 0.9999f);
    PSVECScale(&eff->unk0B4, &eff->unk0B4, 0.9999f);
}

/* 28 insns */
void fn_1_9B58(M575_TUBOEFF *eff, Vec *arm, Vec *point)
{
    Vec torque;
    Vec force;
    PSVECSubtract(&eff->unk0C0, point, &force);
    PSVECAdd(&eff->unk0CC, &force, &eff->unk0CC);
    PSVECCrossProduct(arm, &force, &torque);
    PSVECAdd(&eff->unk0D8, &torque, &eff->unk0D8);
}
