#ifndef M568_MISC_H
#define M568_MISC_H

#include "REL/mgcpp/game.h"

namespace m568 {

/* n.p + d = 0; GC: n +0, d +0xC (0x10). CStage keeps the last hit one at +0x50. */
struct Plane {
    Vec n;   /* 0x0 unit normal */
    float d; /* 0xC */
};

void QuatRotArc(Quaternion* q, const Vec* from, const Vec* to);
/* fn_1_F0F4 (unreferenced): the rotation's axis 'X' / 'Y' / 'Z' (negative = negated); else assert misc.cpp:82.
 * Retail's 'Y' uses 1 - 2(x^2 - z^2) (sic, sheet §7.12; dead code) */
void QuatGetAxis(Vec* out, const Quaternion* q, int axis);
/* fn_1_F384 (unreferenced): out = v - 2 (n.v) n */
void VecReflect(Vec* out, const Vec* n, const Vec* v);
/* fn_1_F424: n = norm((a - b) x (b - c)), d = -(n.a) */
void PlaneFromPoints(Plane* pl, const Vec* a, const Vec* b, const Vec* c);
/* fn_1_F4C4: n.p + d */
float PlaneDist(const Plane* pl, const Vec* p);
/* fn_1_F518: the point where segment a (signed distance da) -> b (db) crosses the plane; b if da == db */
void SegPlane(Vec* out, const Vec* a, float da, const Vec* b, float db);
/* fn_1_F5EC: p inside triangle abc (normal n), edges inclusive */
bool InTriangle(const Vec* a, const Vec* b, const Vec* c, const Vec* p, const Vec* n);

} // namespace m568

#endif
