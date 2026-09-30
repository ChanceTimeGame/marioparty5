/* math.cpp -- three free functions (player_math.md §3.1; .text 884..B24, .rodata 28..60; no .data/.bss/.ctors).
 * EXACT: SubAngle / SubAngleMax are m501 CPlayer::SubAngle / SubAngleMax (= m512 zako) as free functions.
 * Buoyancy (name a guess; unreferenced) written from the asm. */
#include "REL/m511Dll/config.h"
#include "REL/m511Dll/angle.h"

namespace m511 {

float SubAngle(float a, float b)
{
    int ia = DegToAngle(a);
    int ib = DegToAngle(b);
    int d = AngleSub(ia, ib);
    return AngleToDeg(d);
}

float SubAngleMax(float a, float b, float max)
{
    float d = SubAngle(a, b);
    float ret;
    if (d < -max) {
        ret = -max;
    } else if (d > max) {
        ret = max;
    } else {
        ret = d;
    }
    return ret;
}

/* vy minus one frame of gravity (980.665 / 3600, double); below the surface a spring of 0.1 * depth / 3600 */
float Buoyancy(float y, float vy, float surfaceY)
{
    float r = vy - 0.27240694444444447; /* 980.665 / 3600 rounded up (retail bytes 3FD16F1D8965E63E) */
    float d = surfaceY - y;
    if (d > 0.0f) {
        r += (1.0 / 3600.0) * (0.1 * d);
    }
    return r;
}

} // namespace m511
