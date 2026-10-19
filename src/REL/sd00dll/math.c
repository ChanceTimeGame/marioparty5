/*
 * sd00dll math.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sd00dll/asm/REL/sd00dll/math.s.
 */

#include "REL/sd00dll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */

static HuVecF MathVecInterpolate2(HuVecF from, HuVecF to, HuVecF up, float height, float t);

/* --- functions (reference order), .data placed before its first user --- */
/* 30 insns */
void MathMtxRotGet(Mtx mtx, HuVecF *rot)
{
    float temp;
    Hu3DMtxRotGet(mtx, rot);
    if(rot->y == -90.0f) {
        temp = -rot->z;
        rot->z = -rot->x;
        rot->x = temp;
    }
}

/* 77 insns */
void MathMtxRotSet(HuVecF *rot, HuVecF *out, Mtx mtx)
{
    Mtx temp;
    Mtx rotMtx;
    MtxPtr dst = (mtx) ? mtx : temp;
    MTXIdentity(dst);
    MTXRotRad(rotMtx, 'y', MTXDegToRad(rot->y));
    MTXConcat(dst, rotMtx, dst);
    MTXRotRad(rotMtx, 'x', MTXDegToRad(rot->x));
    MTXConcat(dst, rotMtx, dst);
    MTXRotRad(rotMtx, 'z', MTXDegToRad(rot->z));
    MTXConcat(dst, rotMtx, dst);
    MathMtxRotGet(dst, out);
}

/* 121 insns */
void MathPlaneRotMtxGet(HuVecF *dir, HuVecF *up, float roll, Mtx out)
{
    HuVecF upDef[2] = {
        { 0, 1, 0 },
        { 0, 0, 1 }
    };
    Mtx rollMtx;
    HuVecF cross;
    HuVecF cross2;
    HuVecF dirN;
    HuVecF upN;
    float absY;
    VECNormalize(dir, &dirN);
    if(up) {
        VECNormalize(up, &upN);
    } else {
        absY = (dirN.y > 0) ? dirN.y : -dirN.y;
        if(absY < 0.98f) {
            upN = upDef[0];
        } else {
            upN = upDef[1];
        }
    }
    VECCrossProduct(&upN, &dirN, &cross);
    VECNormalize(&cross, &cross);
    VECCrossProduct(&dirN, &cross, &cross2);
    VECNormalize(&cross2, &cross2);
    out[0][0] = cross.x;
    out[1][0] = cross.y;
    out[2][0] = cross.z;
    out[0][1] = cross2.x;
    out[1][1] = cross2.y;
    out[2][1] = cross2.z;
    out[0][2] = dirN.x;
    out[1][2] = dirN.y;
    out[2][2] = dirN.z;
    if(!up) {
        MTXRotDeg(rollMtx, 'z', roll);
        MTXConcat(out, rollMtx, out);
    }
}

/* 53 insns */
HuVecF MathVecInterpolate(HuVecF from, HuVecF to, float height, float t)
{
    HuVecF up = { 0, 1, 0 };
    return MathVecInterpolate2(from, to, up, height, t);
}

/* 152 insns */
static HuVecF MathVecInterpolate2(HuVecF from, HuVecF to, HuVecF up, float height, float t)
{
    HuVecF pos;
    float mag;
    float h;
    VECSubtract(&to, &from, &pos);
    mag = VECMag(&pos);
    if(mag > 0.0f) {
        VECNormalize(&pos, &pos);
        VECScale(&pos, &pos, mag*t);
        VECAdd(&pos, &from, &pos);
    } else {
        pos = from;
    }
    mag = 0.5f-t;
    if(mag < 0.0f) {
        mag = -mag;
    }
    h = 2.0f*(mag*sqrtf(height));
    h = height-(h*h);
    VECNormalize(&up, &up);
    VECScale(&up, &up, h);
    VECAdd(&pos, &up, &pos);
    return pos;
}

/* 44 insns */
void LightColorSet(s16 modelId, s32 matNo, u8 r, u8 g, u8 b)
{
    HSFDATA *hsf;
    HSFMATERIAL *mat;
    s32 i;
    if(modelId == -1) {
        return;
    }
    hsf = Hu3DData[modelId].hsf;
    mat = hsf->material;
    if(matNo == 255) {
        for(i=0; i<hsf->materialNum; i++, mat++) {
            mat->color[0] = r;
            mat->color[1] = g;
            mat->color[2] = b;
        }
    } else if(hsf->materialNum >= matNo) {
        mat[matNo].color[0] = r;
        mat[matNo].color[1] = g;
        mat[matNo].color[2] = b;
    }
}

/* 177 insns */
float MathLerp(s32 mode, float t)
{
    float ret;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
    switch(mode) {
        case 0:
            ret = 1.0-cos(M_PI*(90.0f*t)/180.0);
            break;
        case 1:
            ret = sin(M_PI*(90.0f*t)/180.0);
            break;
        case 2:
            ret = (1.0-cos(M_PI*(180.0f*t)/180.0))/2.0;
            break;
        case 3:
            if(t < 0.5) {
                ret = sin(M_PI*(90.0f*t)/180.0);
            } else {
                ret = 2.0-cos(M_PI*(90.0f*t)/180.0);
            }
            ret *= 0.5f;
            break;
        case 4:
            ret = t;
            break;
        case 5:
            ret = sin(M_PI*(180.0f*t)/180.0);
            break;
    }
    return ret;
}

/* 67 insns */
void MathRotVecMulti(HuVecF *rot, s32 num, HuVecF *in, HuVecF *out)
{
    Mtx mtx;
    Mtx rotMtx;
    s32 i;
    MTXIdentity(mtx);
    MTXRotRad(rotMtx, 'y', MTXDegToRad(rot->y));
    MTXConcat(mtx, rotMtx, mtx);
    MTXRotRad(rotMtx, 'x', MTXDegToRad(rot->x));
    MTXConcat(mtx, rotMtx, mtx);
    MTXRotRad(rotMtx, 'z', MTXDegToRad(rot->z));
    MTXConcat(mtx, rotMtx, mtx);
    for(i=0; i<num; i++) {
        MTXMultVec(mtx, &in[i], &out[i]);
    }
}

/* 27 insns */
void MathMultVecMulti(Mtx mtx, s32 num, HuVecF *in, HuVecF *out)
{
    s32 i;
    for(i=0; i<num; i++) {
        MTXMultVec(mtx, &in[i], &out[i]);
    }
}
