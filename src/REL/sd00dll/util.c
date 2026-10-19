/*
 * sd00dll util.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sd00dll/asm/REL/sd00dll/util.s.
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
#include "game/frand.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */

/* --- functions (reference order), .data placed before its first user --- */
/* 225 insns */
HuVecF SdRandomPosGet(s32 mode, HuVecF center, HuVecF *axis, float max, float min)
{
    HuVecF pos = { 0, 0, 0 };
    HuVecF upTbl[2] = {
        { 0, 1, 0 },
        { 1, 0, 0 }
    };
    Mtx rotMtx;
    Mtx rotMtx2;
    HuVecF axisN;
    float dot;
    HuVecF *up;
    if(mode == 0) {
        if(axis) {
            /* retail bug: normalizes the parameter slot itself (&axis), not *axis; every caller passes NULL */
            VECNormalize((HuVecF *)&axis, &axisN);
            dot = VECDotProduct(&axisN, &upTbl[0]);
            if(dot < 0.707f && dot > -0.707f) {
                up = &upTbl[0];
            } else {
                up = &upTbl[1];
            }
            VECCrossProduct(&axisN, up, &pos);
            VECNormalize(&pos, &pos);
            VECScale(&pos, &pos, min+frandmod(max-min));
            MTXRotAxisRad(rotMtx, &axisN, MTXDegToRad((float)frandmod(360)));
            MTXMultVec(rotMtx, &pos, &pos);
        } else {
            pos.x = min+frandmod(max-min);
            MTXRotRad(rotMtx, 'y', MTXDegToRad((float)frandmod(360)));
            MTXMultVec(rotMtx, &pos, &pos);
        }
    } else {
        pos.x = min+frandmod(max-min);
        MTXRotRad(rotMtx, 'x', MTXDegToRad((float)frandmod(180)-90.0f));
        MTXRotRad(rotMtx2, 'y', MTXDegToRad((float)frandmod(360)));
        MTXConcat(rotMtx, rotMtx2, rotMtx);
        MTXMultVec(rotMtx, &pos, &pos);
    }
    VECAdd(&pos, &center, &pos);
    return pos;
}

/* 50 insns */
void SdModelGlowSet(s16 modelId)
{
    HSFDATA *hsf = Hu3DData[modelId].hsf;
    HSFMATERIAL *mat = hsf->material;
    mat[2].litColor[0] = 0;
    mat[2].litColor[1] = 0;
    mat[2].litColor[2] = 0;
    mat[2].color[0] = 25;
    mat[2].color[1] = 25;
    mat[2].color[2] = 76;
    mat[2].shadowColor[0] = 255;
    mat[2].shadowColor[1] = 255;
    mat[2].shadowColor[2] = 255;
    mat[3].litColor[0] = 0;
    mat[3].litColor[1] = 0;
    mat[3].litColor[2] = 0;
    mat[3].color[0] = 25;
    mat[3].color[1] = 25;
    mat[3].color[2] = 76;
    mat[3].shadowColor[0] = 255;
    mat[3].shadowColor[1] = 255;
    mat[3].shadowColor[2] = 255;
}

/* 150 insns */
void SdScreenPosGet(HuVecF *pos, s16 cameraBit, HuVecF *out)
{
    s16 i;
    HU3DCAMERA *camera;
    Mtx lookAt;
    HuVecF viewPos;
    float x;
    float y;
    for(i=0; i<16; i++) {
        if(cameraBit & (1 << i)) {
            break;
        }
    }
    camera = &Hu3DCamera[i];
    C_MTXLookAt(lookAt, &camera->pos, &camera->up, &camera->target);
    MTXMultVec(lookAt, pos, &viewPos);
    x = (viewPos.z*(HuSin(camera->fov/2.0f)/HuCos(camera->fov/2.0f)))*1.2f;
    y = viewPos.z*(HuSin(camera->fov/2.0f)/HuCos(camera->fov/2.0f));
    out->x = 288.0f+(viewPos.x*(288.0f/-x));
    out->y = 240.0f+(viewPos.y*(240.0f/y));
    out->z = viewPos.z;
}
