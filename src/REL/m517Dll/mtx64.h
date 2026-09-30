/* mtx64.h -- the double-precision vector helpers of retail's "mtx64.h" (Normalize asserts mtx64.h:112), declared in
 * misc.h. Settled (F6): plain external functions -- all eleven are raw-identical in this form, and a class or
 * template form would make them inline/weak (inlined into misc.cpp's callers, which retail calls out of line).
 * MagSq / Mag spilling r3 is the REL flags' -O0 parameter handling, not a `this`. Included ONCE, by misc.cpp after
 * InTriangle, so CW emits them there in retail order (F6AC..FA78) with the retail __FILE__ / __LINE__
 * (CW's #line does not change __FILE__). The assert must stay on line 112 (test/fixlines.py). */
#ifndef M517_MTX64_H
#define M517_MTX64_H

#include "REL/m517Dll/misc.h"
#include "REL/mgcpp/assert.h"

namespace m517 {

/* line padding: the assert below is retail's mtx64.h:112 */





























































































Vec64* Normalize(const Vec64* v, Vec64* out)
{
    double mag = Mag(v);
    assert(mag != 0.0);
    return Scale(v, out, 1.0 / mag);
}

Vec64* Scale(const Vec64* v, Vec64* out, double s)
{
    out->x = v->x * s;
    out->y = v->y * s;
    out->z = v->z * s;
    return out;
}

Vec64* Scale2(const Vec64* v, Vec64* out, double s)
{
    out->x = v->x * s;
    out->y = v->y * s;
    out->z = v->z * s;
    return out;
}

double Mag(const Vec64* v)
{
    return sqrt(MagSq(v));
}

double MagSq(const Vec64* v)
{
    return Dot(v, v);
}

Vec64* Cross(const Vec64* a, const Vec64* b, Vec64* out)
{
    out->x = a->y * b->z - a->z * b->y;
    out->y = a->z * b->x - a->x * b->z;
    out->z = a->x * b->y - a->y * b->x;
    return out;
}

double Dot(const Vec64* a, const Vec64* b)
{
    return a->z * b->z + (a->x * b->x + a->y * b->y);
}

double Dot2(const Vec64* a, const Vec64* b)
{
    return a->z * b->z + (a->x * b->x + a->y * b->y);
}

double DotV(const Vec64* a, const Vec* b)
{
    return a->z * b->z + (a->x * b->x + a->y * b->y);
}

Vec64* Sub(const Vec* a, const Vec* b, Vec64* out)
{
    out->x = (double)a->x - b->x;
    out->y = (double)a->y - b->y;
    out->z = (double)a->z - b->z;
    return out;
}

Vec64* Add(const Vec* a, const Vec64* b, Vec64* out)
{
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
    return out;
}

} // namespace m517

#endif
