#ifndef M521_DEBUGLINE_H
#define M521_DEBUGLINE_H

#include "REL/mgcpp/game.h"

namespace m521 {

class CDebugLine {
public:
    static void DrawHook(HU3DMODEL* model, Mtx* mtx); /* fn_1_AADC */
    CDebugLine();                                     /* fn_1_AB20 (unreferenced) */
    ~CDebugLine();                                    /* fn_1_AC20 (unreferenced) */
    void draw(Mtx* mtx);                              /* fn_1_AC74 v1 = (end.x, end.y, START.z): retail */

    HU3DMODELID m_model; /* 0x00 */
    Vec m_start;         /* 0x04 */
    Vec m_end;           /* 0x10 */
    GXColor m_color;     /* 0x1C */
};

} // namespace m521

#endif
