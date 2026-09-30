/* angle.h (named so, not math.h: MSVC resolves a DOL header's quoted "math.h" against the includer's directory) -- math.cpp (.text 884..B24, .rodata 28..60; its own TU, no .data/.bss/.ctors): three free angle / float
 * helpers (player_math.md §3.1). Only SubAngle is referenced (player x3, staryaji Update); SubAngleMax and Buoyancy
 * are dead. SubAngle/SubAngleMax are m501's CPlayer::SubAngle/SubAngleMax (masked 0-diff) as free functions.
 * The degree <-> 16-bit angle inlines are m512 player.h's. */
#ifndef M511_ANGLE_H
#define M511_ANGLE_H

#include "REL/mgcpp/game.h"

namespace m511 {

inline int DegToAngle(float deg)
{
    return (65536.0 / 360.0) * deg;
}

inline float AngleToDeg(int angle)
{
    return (360.0 / 65536.0) * angle;
}

inline int AngleSub(int a, int b)
{
    return ((a - b - 0x8000) & 0xFFFF) - 0x8000;
}

float SubAngle(float a, float b);               /* fn_1_884 wrapped a - b in degrees (-180, 180] */
float SubAngleMax(float a, float b, float max); /* fn_1_93C unreferenced: clamped to +-max */
/* fn_1_AA0 unreferenced (name a guess): vy - g/3600 (+ 0.1 * depth / 3600 below the surface) */
float Buoyancy(float y, float vy, float surfaceY);

} // namespace m511

#endif
