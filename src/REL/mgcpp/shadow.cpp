/* shadow.cpp -- the two shadow-camera helpers m532/m539 carry between random.cpp and sphere.cpp (plan Phase 4
 * framework survey; m539 fn_1_501C/fn_1_50C4 = m532 fn_1_6FDC/fn_1_7084). Names are ours.
 * ShadowCamPos is raw-identical; its copy inlined into ShadowSetup is at the reference count with only the
 * placement of two dead pointer hops differing (m539 W1 2026-09-25: the `const float&` scale argument and the
 * returned-pointer wrapper are what reproduce retail's register hops). */
#include "REL/mgcpp/game.h"

/* up vectors: {0,1,0} unless the light is nearly vertical */
static const Vec s_shadowUp[2] = { { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } };

static inline Vec* ShadowScale(Vec* src, Vec* dst, const float& k)
{
    PSVECScale(src, dst, k);
    return dst;
}

static inline void ShadowSub(Vec* a, Vec* b, Vec* out)
{
    PSVECSubtract(a, b, out);
}

/* camera position `radius / tan(5 deg)` back from `target` along `dir`; returns that distance */
float ShadowCamPos(Vec* out, Vec* dir, Vec* target, float radius)
{
    float dist = radius / tan(MTXDegToRad(5.0f));
    Vec* v = ShadowScale(dir, out, dist);
    PSVECSubtract(target, v, v);
    return dist;
}

/* one shadow camera for a single camera bit, a multi-shadow otherwise */
void ShadowSetup(s16 camBit, Vec* lightDir, Vec* target, float size, float depth)
{
    size *= 0.5f;
    depth *= 0.5f;
    Vec pos;
    Vec dir;
    PSVECNormalize(lightDir, &dir);
    int idx;
    if (fabs(dir.y) < 0.5) {
        idx = 0;
    } else {
        idx = 1;
    }
    const Vec* up = &s_shadowUp[idx];
    float dist = ShadowCamPos(&pos, &dir, target, size);
    float near = dist - depth;
    float far = dist + depth;
    int n = 0;
    for (int i = 0; i < 16; i++) {
        if (camBit & (1 << i)) {
            n++;
        }
    }
    if (n < 2) {
        Hu3DShadowCreate(10.0f, near, far);
        Hu3DShadowPosSet(&pos, (Vec*)up, target);
        Hu3DShadowSizeSet(480);
        Hu3DShadowTPLvlSet(0.4f);
    } else {
        Hu3DShadowMultiCreate(10.0f, near, far, camBit);
        Hu3DShadowMultiPosSet(&pos, (Vec*)up, target, camBit);
        Hu3DShadowMultiSizeSet(480, camBit);
        Hu3DShadowMultiTPLvlSet(0.4f, camBit);
    }
}
