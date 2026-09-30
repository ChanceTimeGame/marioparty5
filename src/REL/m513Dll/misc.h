#ifndef M513_MISC_H
#define M513_MISC_H

#include "REL/mgcpp/game.h"

namespace m513 {

/* mtx64.h: 3 doubles (0x18) */
struct Vec64 {
    double x;
    double y;
    double z;
};

/* n.p + d = 0; GC: n +0, d +0x18 (0x20) */
struct Plane64 {
    Vec64 n;
    double d;
};

/* PSVEC calls returning the result by reference: Spring's nested use materialises the returned reference
 * (addi; mr); Spring returns VecAdd(...) by value (a word copy into the hidden result). Defined here so misc.cpp
 * keeps its retail assert line */
inline Vec& VecSub(const Vec* a, const Vec* b, Vec* d)
{
    PSVECSubtract(a, b, d);
    return *d;
}

inline Vec& VecScale(const Vec* v, Vec* d, float s)
{
    PSVECScale(v, d, s);
    return *d;
}

inline Vec& VecAdd(const Vec* a, const Vec* b, Vec* d)
{
    PSVECAdd(a, b, d);
    return *d;
}

inline float VecMag(const Vec* v)
{
    return PSVECMag(v);
}

inline float VecDot(const Vec* a, const Vec* b)
{
    return PSVECDotProduct(a, b);
}

/* fn_1_10964 (returns the Vec by value: hidden result pointer r3): a + normalize(a - b) * (k (rest - |a - b|) + damp ((a - b).v / |a - b|)), v = (bPrev - b) s */
Vec Spring(const Vec* a, const Vec* b, const Vec* bPrev, float s, float k, float damp, float rest);
/* fn_1_10AB8 (= m568 ED98): the shortest-arc rotation taking `from` to `to` */
void QuatRotArc(Quaternion* q, const Vec* from, const Vec* to);
/* fn_1_10E14: the rotation's axis 'X' / 'Y' / 'Z' (negative = negated); else assert misc.cpp:80 */
void QuatGetAxis(Vec* out, const Quaternion* q, int axis);
/* fn_1_110A4: out = v - 2 (n.v) n */
void VecReflect(Vec* out, const Vec* n, const Vec* v);
/* fn_1_11144: n = Normalize((a - b) x (b - c)), d = -(n.a) */
void PlaneFromPoints(Plane64* pl, const Vec* a, const Vec* b, const Vec* c);
/* fn_1_111D8: n.p + d */
double PlaneDist(const Plane64* pl, const Vec* p);
/* fn_1_11218: where segment a (signed distance da) -> b (db) crosses the plane; b if db == da */
void SegPlane(Vec* out, const Vec* a, double da, const Vec* b, double db);
/* fn_1_11310: p inside triangle abc (normal n), edges inclusive */
bool InTriangle(const Vec* a, const Vec* b, const Vec* c, const Vec* p, const Vec64* n);

/* the mtx64.h helpers, in retail order (11440..1180C; none is inlined: each is defined after its callers) */
Vec64* Normalize(const Vec64* v, Vec64* out);            /* fn_1_11440 assert mag != 0.0 (mtx64.h:112) */
Vec64* Scale(const Vec64* v, Vec64* out, double s);      /* fn_1_114CC */
Vec64* Scale2(const Vec64* v, Vec64* out, double s);     /* fn_1_114F8 same body, a distinct function */
double Mag(const Vec64* v);                              /* fn_1_11524 inline MSL sqrt(MagSq) */
double MagSq(const Vec64* v);                            /* fn_1_116A8 Dot(v, v) */
Vec64* Cross(const Vec64* a, const Vec64* b, Vec64* out); /* fn_1_116DC */
double Dot(const Vec64* a, const Vec64* b);              /* fn_1_11744 */
double Dot2(const Vec64* a, const Vec64* b);             /* fn_1_11774 same body, a distinct function */
double DotV(const Vec64* a, const Vec* b);               /* fn_1_117A4 */
Vec64* Sub(const Vec* a, const Vec* b, Vec64* out);      /* fn_1_117D4 */
Vec64* Add(const Vec* a, const Vec64* b, Vec64* out);    /* fn_1_1180C */

} // namespace m513

#endif
