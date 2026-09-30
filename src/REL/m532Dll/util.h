/* util.h -- m532's small inline helpers (inline only: nothing here is emitted out of line).
 * SetVec: the m501/m536/m512 setter with DOUBLE components (retail stores each component with `frsp; stfs`:
 *   ball 7A4..7EC / 1654..1670, man_referee BCE4..BD00).
 * HuSprTexLoad / GXSetVtxAttrFmtv: prototypes the headers lack.
 * M532_GRAVITY: 980.665 / 3600 (standard g in cm per frame^2 at 60 fps), 0x3E8B78EC in ball/man_referee. */
#ifndef M532_UTIL_H
#define M532_UTIL_H

#include "REL/mgcpp/game.h"

extern "C" {
/* no live prototype (game/sprite.h has it commented out); as m531 cleaneff.cpp / m502 / m505 */
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
void GXSetVtxAttrFmtv(GXVtxFmt vtxfmt, GXVtxAttrFmtList* list);
}

#define M532_GRAVITY 0.27240694f

namespace m532 {

inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

/* d = a - b, returns |d|: the length reaches the caller through the inline's temporaries (a local: fmr x3,
 * CHangBall::Move BE0 / CBall::CheckArrive 1A58; a member store: fmr x2, CBall ctor 13FC / throwTo 1784) */
inline float VecSubMag(Vec* a, Vec* b, Vec* d)
{
    PSVECSubtract(a, b, d);
    return PSVECMag(d);
}

} // namespace m532

#endif
