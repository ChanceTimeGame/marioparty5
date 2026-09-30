#ifndef M517_DUSTEFF_H
#define M517_DUSTEFF_H

#include "REL/mgcpp/game.h"

namespace m517 {

class CShadow {
public:
    static void DrawHook(HU3DMODEL* model, Mtx* mtx); /* fn_1_BDB0 -> Draw */
    CShadow();                                        /* fn_1_BDF4 */
    ~CShadow();                                       /* fn_1_BEDC (kuribo) */
    void Draw(Mtx* view);                             /* fn_1_BF38 */

    ANIMDATA* m_anim;     /* 0x00 0x4B0013 */
    Vec m_pos;            /* 0x04 written by the owner */
    HU3DMODELID m_model;  /* 0x10 Hu3DHookFuncCreate(DrawHook) */
    GXColor m_color;      /* 0x12 {0, 0, 0x40, 0x40} (BEA0..BEBC) */
};

class CShadow2 {
public:
    static void DrawHook(HU3DMODEL* model, Mtx* mtx); /* fn_1_C3E8 -> Draw */
    CShadow2();                                       /* fn_1_C42C */
    ~CShadow2();                                      /* fn_1_C4F4 (gamemaster, player) */
    void Draw(Mtx* view);                             /* fn_1_C550 */

    ANIMDATA* m_anim;     /* 0x00 0x4B0013 */
    Vec m_pos;            /* 0x04 written by the owner (player: pos + (0, 5, 0)) */
    HU3DMODELID m_model;  /* 0x10 */
};

} // namespace m517

#endif
