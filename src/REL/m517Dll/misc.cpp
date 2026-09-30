#include "REL/m517Dll/misc.h"
#include "REL/mgcpp/assert.h"

namespace m517 {

/* fn_1_EBD0: the three calls of the force are evaluated right to left (|d|, d.v, |d|) */
Vec Spring(const Vec* a, const Vec* b, const Vec* bPrev, float s, float k, float damp, float rest)
{
    Vec d;
    Vec vs;
    Vec v;
    VecSub(a, b, &d);
    VecScale(&VecSub(bPrev, b, &v), &vs, s);
    float f = k * (rest - VecMag(&d)) + damp * (VecDot(&d, &vs) / VecMag(&d));
    PSVECNormalize(&d, &d);
    PSVECScale(&d, &d, f);
    return VecAdd(&d, a, &v);
}

/* fn_1_ED24 (= m568 ED98): s is a double; w = s / 2.0 (fmul s, 0.5 in that order) */
void QuatRotArc(Quaternion* q, const Vec* from, const Vec* to)
{
    Vec a, b, c;
    PSVECNormalize(from, &a);
    PSVECNormalize(to, &b);
    float d = PSVECDotProduct(&a, &b);
    double t = d;
    double s = sqrt(2.0 + 2.0 * t);
    q->w = s / 2.0;
    s = 1.0 / s;
    PSVECCrossProduct(&a, &b, &c);
    q->x = c.x * s;
    q->y = c.y * s;
    q->z = c.z * s;
}

/* line padding: the assert below is retail's misc.cpp:81 (m513: 80) */








/* fn_1_F080: the components are doubles until the final stores */
void QuatGetAxis(Vec* out, const Quaternion* q, int axis)
{
    double x = q->x, y = q->y, z = q->z, w = q->w;
    bool neg = axis < 0;
    double ox, oy, oz;
    switch (neg ? -axis : axis) {
    case 'X':
        ox = 1.0 + -2.0 * (y * y + z * z);
        oy = 2.0 * (x * y - w * z);
        oz = 2.0 * (x * z + w * y);
        break;
    case 'Y':
        ox = 2.0 * (x * y + w * z);
        oy = 1.0 + -2.0 * (x * x - z * z);
        oz = 2.0 * (y * z + w * x);
        break;
    case 'Z':
        ox = 2.0 * (x * z + w * y);
        oy = 2.0 * (y * z - w * x);
        oz = 1.0 + -2.0 * (x * x + y * y);
        break;
    default:
        assert(!"Invalid Axis");
        return;
    }
    if (neg) {
        ox = -ox;
        oy = -oy;
        oz = -oz;
    }
    out->x = ox;
    out->y = oy;
    out->z = oz;
}

void VecReflect(Vec* out, const Vec* n, const Vec* v)
{
    float k;
    float dot = PSVECDotProduct(n, v);
    k = -2.0f * dot;
    PSVECScale(n, out, k);
    PSVECAdd(v, out, out);
}

/* STUB detail (fn_1_F3B0, 37 insns) */
void PlaneFromPoints(Plane64* pl, const Vec* a, const Vec* b, const Vec* c)
{
    Vec64 ab;
    Vec64 bc;
    Sub(a, b, &ab);
    Sub(b, c, &bc);
    Cross(&ab, &bc, &pl->n);
    Normalize(&pl->n, &pl->n);
    pl->d = -DotV(&pl->n, a);
}

double PlaneDist(const Plane64* pl, const Vec* p)
{
    return DotV(&pl->n, p) + pl->d;
}

/* fn_1_F484 (m568 F518 in doubles) */
void SegPlane(Vec* out, const Vec* a, double da, const Vec* b, double db)
{
    double den = db - da;
    if (den != 0.0) {
        Vec64 d;
        Sub(b, a, &d);
        Scale2(&d, &d, -da / den);
        Add(a, &d, &d);
        out->x = d.x;
        out->y = d.y;
        out->z = d.z;
    } else {
        *out = *b;
    }
}

/* fn_1_F57C (m568 F5EC in doubles): Cross returns its result pointer straight into Dot2 */
bool InTriangle(const Vec* a, const Vec* b, const Vec* c, const Vec* p, const Vec64* n)
{
    Vec64 pa;
    Vec64 pb;
    Vec64 pc;
    Vec64 x;
    Sub(a, p, &pa);
    Sub(b, p, &pb);
    Sub(c, p, &pc);
    bool in = false;
    bool ab = false;
    if (Dot2(Cross(&pa, &pb, &x), n) >= 0.0 && Dot2(Cross(&pb, &pc, &x), n) >= 0.0) {
        ab = true;
    }
    if (ab && Dot2(Cross(&pc, &pa, &x), n) >= 0.0) {
        in = true;
    }
    return in;
}

} // namespace m517

/* retail's mtx64.h double helpers: defined there (its assert names "mtx64.h"), emitted here, after InTriangle */
#include "REL/m517Dll/mtx64.h"
