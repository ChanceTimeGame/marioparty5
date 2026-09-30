#include "REL/m568Dll/misc.h"
#include "REL/mgcpp/assert.h"

namespace m568 {

/* fn_1_ED98: s is a double (retail keeps it in a double register through w and 1/s) */
void QuatRotArc(Quaternion* q, const Vec* from, const Vec* to)
{
    Vec a;
    Vec b;
    Vec c;
    PSVECNormalize(from, &a);
    PSVECNormalize(to, &b);
    float d = PSVECDotProduct(&a, &b);
    double t = d;
    double s = sqrt(2.0 + 2.0 * t);
    q->w = s * 0.5;
    s = 1.0 / s;
    PSVECCrossProduct(&a, &b, &c);
    q->x = c.x * s;
    q->y = c.y * s;
    q->z = c.z * s;
}

/* line padding: the assert below is retail's misc.cpp:82 */












/* fn_1_F0F4 (unreferenced): the components are doubles until the final stores */
void QuatGetAxis(Vec* out, const Quaternion* q, int axis)
{
    double x = q->x;
    double y = q->y;
    double z = q->z;
    double w = q->w;
    bool neg = axis < 0;
    double ox;
    double oy;
    double oz;
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

void PlaneFromPoints(Plane* pl, const Vec* a, const Vec* b, const Vec* c)
{
    Vec ab;
    Vec bc;
    PSVECSubtract(a, b, &ab);
    PSVECSubtract(b, c, &bc);
    PSVECCrossProduct(&ab, &bc, &pl->n);
    PSVECNormalize(&pl->n, &pl->n);
    float dot = PSVECDotProduct(&pl->n, a);
    pl->d = -dot;
}

float PlaneDist(const Plane* pl, const Vec* p)
{
    float dot = PSVECDotProduct(&pl->n, p);
    return pl->d + dot;
}

void SegPlane(Vec* out, const Vec* a, float da, const Vec* b, float db)
{
    float den = db - da;
    if (den != 0.0f) {
        Vec d;
        PSVECSubtract(b, a, &d);
        PSVECScale(&d, &d, -da / den);
        PSVECAdd(a, &d, out);
    } else {
        *out = *b;
    }
}

/* fn_1_F5EC: each dot product is copied once more before its test (fmr, fmr) */
bool InTriangle(const Vec* a, const Vec* b, const Vec* c, const Vec* p, const Vec* n)
{
    Vec pa;
    Vec pb;
    Vec pc;
    Vec x;
    PSVECSubtract(a, p, &pa);
    PSVECSubtract(b, p, &pb);
    PSVECSubtract(c, p, &pc);
    bool in = false;
    bool ab = false;
    PSVECCrossProduct(&pa, &pb, &x);
    float d0 = PSVECDotProduct(&x, n);
    float t0 = d0;
    if (t0 >= 0.0f) {
        PSVECCrossProduct(&pb, &pc, &x);
        float d1 = PSVECDotProduct(&x, n);
        float t1 = d1;
        if (t1 >= 0.0f) {
            ab = true;
        }
    }
    if (ab) {
        PSVECCrossProduct(&pc, &pa, &x);
        float d2 = PSVECDotProduct(&x, n);
        float t2 = d2;
        if (t2 >= 0.0f) {
            in = true;
        }
    }
    return in;
}

} // namespace m568
