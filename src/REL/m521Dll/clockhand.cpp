/* clockhand.cpp -- m521::CClockHand (clockhand.h). Retail order (sheet clock_clockhand_player.md §3.2): ctor,
 * SetAngle, dtor. No .data / .bss / .ctors (no minigame.h). .rodata 0x118: 0.0, pi/180. */
#include "REL/m521Dll/clockhand.h"

namespace m521 {

/* fn_1_48FC */
CClockHand::CClockHand(u32 dataNum, Mtx base) : m_model(dataNum)
{
    HU3DMODELID id = m_model.id();
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
    PSMTXCopy(base, m_base);
    m_angle = 0.0f;
}

void CClockHand::SetAngle(float deg)
{
    Mtx rot;
    m_angle = deg;
    PSMTXRotRad(rot, 'Y', 0.017453292f * deg);
    PSMTXConcat(m_base, rot, m_mtx);
    Mtx* mtx = m_model.getMatrix();
    PSMTXCopy(m_mtx, *mtx);
}

/* fn_1_4A10: ~CModel(-1) (member) */
CClockHand::~CClockHand() {}

} // namespace m521
