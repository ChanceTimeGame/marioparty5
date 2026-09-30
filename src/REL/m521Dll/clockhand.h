#ifndef M521_CLOCKHAND_H
#define M521_CLOCKHAND_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"

namespace m521 {

class CClockHand {
public:
    CClockHand(u32 dataNum, Mtx base); /* fn_1_48FC ShadowSet + ShadowDispOn; m_base = base; m_angle = 0 */
    void SetAngle(float deg);          /* fn_1_4984 */
    ~CClockHand();                     /* fn_1_4A10 */
    /* the current frame (clock: GetHandPos / GetHandPoint / the hit tests; inline, W1 addition) */
    MtxPtr GetMtx() { return m_mtx; }

    CModel m_model; /* 0x00 */
    Mtx m_base;     /* 0x04 the pivot frame (built by CClock()) */
    Mtx m_mtx;      /* 0x34 m_base * RotY(m_angle): read by clock's hit tests / GetHandPos / GetHandPoint */
    float m_angle;  /* 0x64 degrees */
};

} // namespace m521

#endif
