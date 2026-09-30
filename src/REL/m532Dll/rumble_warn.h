/* rumble_warn.h -- rumble_warn.cpp: m532::CRumbleWarn, the visual substitute for controller rumble: a two-texture
 * billboard icon (0x5A0018 / 0x5A0019) over a player's head, created by CPlayer::rumble(1) when a pad cannot
 * rumble; shown for s_reactTime - 1 frames (procShow), then it deletes itself (update).
 * GC: CObject +0 (vptr +0xC), m_proc +0x14 (12-byte PTMF), m_anim0 +0x20, m_anim1 +0x24, m_w +0x28, m_h +0x2C,
 * m_pos +0x30, m_scale +0x3C, m_alpha +0x40, m_count +0x44; size 0x48 (player `li r3,0x48`).
 * Vtable data_304 {~ 8298, update 830C, draw 8528, onFinish 1AFC} + a pad word.
 * procGrow / procHold / procFade are dead (no PTMF reaches procGrow). Names are ours. */
#ifndef M532_RUMBLE_WARN_H
#define M532_RUMBLE_WARN_H

#include "REL/m532Dll/config.h"
#include "REL/mgcpp/game.h"
#include "REL/m532Dll/man_object.h"

namespace m532 {

class CRumbleWarn : public CObject {
public:
    typedef bool (CRumbleWarn::*ProcFunc)();

    CRumbleWarn(Vec* pos);        /* fn_1_8130 */
    virtual ~CRumbleWarn();       /* fn_1_8298 */
    virtual void update();        /* fn_1_830C deletes this when the proc returns false */
    bool procGrow();              /* fn_1_8380 dead */
    bool procHold();              /* fn_1_8418 dead (only procGrow leads here) */
    bool procFade();              /* fn_1_8480 dead */
    bool procShow();              /* fn_1_84D8 the only live proc */
    virtual void draw(Mtx* view);

    /* PTMF stores go through a by-value copy (three words to a stack temp) */
    void setProc(ProcFunc proc) { m_proc = proc; }

    ProcFunc m_proc;    /* 0x14 (12 bytes on CW) */
    ANIMDATA* m_anim0;  /* 0x20 0x5A0018 (locked; killed by the dtor) */
    ANIMDATA* m_anim1;  /* 0x24 0x5A0019 */
    float m_w;          /* 0x28 m_anim0 bmp sizeX */
    float m_h;          /* 0x2C m_anim0 bmp sizeY */
    Vec m_pos;          /* 0x30 */
    float m_scale;      /* 0x3C */
    float m_alpha;      /* 0x40 */
    int m_count;        /* 0x44 frames */
};

} // namespace m532

#endif
