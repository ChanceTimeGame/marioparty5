/* sphere.cpp -- the sphere helpers (declared in om.h). In m501 they follow om.cpp directly; in the overlays
 * that carry random.cpp in the framework unit they follow it, so they are a file of their own (plan Phase 4
 * framework survey). m522/m537 do not have them; m532/m539 carry a 159-instruction HitPushSphere (open). */
#include "REL/mgcpp/om.h"

/* Vec helpers. Retail inlines three small helpers here: their return values and arguments are what put
 * the Mag result and the scaled vector through extra registers (fn_1_4F0C/fn_1_4FB4). Names are ours. */
static inline float VecMag(Vec* v)
{
    return PSVECMag(v);
}

static inline Vec* VecScale(Vec* src, Vec* dst, float s)
{
    PSVECScale(src, dst, s);
    return dst;
}

static inline void VecAdd(Vec* a, Vec* b, Vec* out)
{
    PSVECAdd(a, b, out);
}

/* fn_1_4F0C: do the spheres overlap? Unreferenced. */
bool HitCheckSphere(CSphere* a, CSphere* b)
{
    float sum;
    Vec d;
    PSVECSubtract(&a->pos, &b->pos, &d);
    sum = a->radius() + b->radius();
    return VecMag(&d) < sum;
}

/* fn_1_4FB4: if the spheres overlap, push them apart along the centre line by k * overlap, a taking
 * `ratio` of it and b the rest. Returns whether they overlapped.
 * Retail: dist == 0 (coincident centres) divides by zero -- not guarded (unreachable in practice). */
bool HitPushSphere(CSphere* a, CSphere* b, float ratio, float k)
{
    float dist, sum, ratioA, ratioB;
    Vec d, t;
    sum = a->radius() + b->radius();
    PSVECSubtract(&b->pos, &a->pos, &d);
    dist = VecMag(&d);
    if (dist >= sum) {
        return false;
    }
    ratioA = ratio;
    ratioB = 1.0f - ratio;
    PSVECScale(&d, &d, k * (sum - dist) / dist);
    VecAdd(VecScale(&d, &t, -ratioA), &a->pos, &a->pos);
    VecAdd(VecScale(&d, &t, ratioB), &b->pos, &b->pos);
    return true;
}
