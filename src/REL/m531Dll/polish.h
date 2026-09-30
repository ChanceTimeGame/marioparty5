/* polish.h -- particle/draw effects on effect.h's bases (polish.cpp; names ours, the player sheet's):
 *   CLandSmoke  0x10  landing smoke ring (player UpdateEnter), 0x590002 x8; deletes itself when every puff is gone
 *   CSpray      0x10  endless spray (CStageObjects' m_polish), 0x590003
 *   CConfetti   0x10  confetti burst (flow mode 5), 0x590004 x10, additive; deletes itself when done
 *   CSparkle    0x28  endless sparkles around the brush (CPlayer::m_sparkle), 0x590004 x32
 *   CDebugRect  0x28  a CHookEffect drawing an XZ rectangle outline; never constructed (dead)
 * Vtables (.data, reverse class order): data_168 CDebugRect {on_update 7120, draw 7124, ~ 70BC},
 * data_17C CSparkle {~ 74E0, on_hook 6A8C}, data_18C CConfetti {~ 6654, 6168}, data_19C CSpray {~ 7544, 5DFC},
 * data_1AC CLandSmoke {~ 5CC4, 57DC}. ~CSparkle / ~CSpray sit at the unit end: implicit (not declared).
 * Every derived ctor sets Hu3DParticleHookSet(m_model, CParticleEffect::Hook) itself (retail R7).
 * The particle counts are `int` (the ctors spill them as words: stw/lwz, not sth/lha). */
#ifndef M531_POLISH_H
#define M531_POLISH_H

#include "REL/m531Dll/effect.h"

namespace m531 {

class CLandSmoke : public CParticleEffect {
public:
    CLandSmoke(Vec pos);                   /* fn_1_5700 (player 9758: by-value Vec) */
    virtual void on_hook(Mtx mtx);         /* fn_1_57DC (`delete this` when no puff is alive) */
    virtual ~CLandSmoke();                 /* fn_1_5CC4 */
};

class CSpray : public CParticleEffect {
public:
    CSpray(u32 dataNum, int count, Vec pos, Vec rot); /* fn_1_5D28 (object 7DB4: by-value Vecs) */
    virtual void on_hook(Mtx mtx);         /* fn_1_5DFC */
    /* ~CSpray fn_1_7544: implicit */
};

class CConfetti : public CParticleEffect {
public:
    CConfetti(int count, Vec pos, Vec rot); /* fn_1_6080 (flow mode 5: by-value Vecs) */
    virtual void on_hook(Mtx mtx);         /* fn_1_6168 (`delete this` when every piece has faded) */
    virtual ~CConfetti();                  /* fn_1_6654 */
};

class CSparkle : public CParticleEffect {
public:
    Vec m_center;                          /* 0x10 SetPos (the brush position) */
    Vec m_rot;                             /* 0x1C SetRot (stored, never read) */

    CSparkle(int count, Vec center, Vec rot); /* fn_1_66B8 ends hidden (hide); player 945C: by-value Vecs */
    void Respawn(HU3DPARTICLEDATA* data);  /* fn_1_6808 no caller: inlined twice into on_hook */
    virtual void on_hook(Mtx mtx);         /* fn_1_6A8C */
    void SetPos(Vec* pos);                 /* fn_1_7030 */
    void SetRot(Vec* rot);                 /* fn_1_704C */
    /* ~CSparkle fn_1_74E0: implicit */
};

class CDebugRect : public CHookEffect {
public:
    Vec m_min;                             /* 0x10 never written (the ctor takes no bounds) */
    Vec m_max;                             /* 0x1C */

    CDebugRect(Process_s* om);             /* fn_1_7068 no caller */
    virtual ~CDebugRect();                 /* fn_1_70BC */
    virtual void on_update();              /* fn_1_7120 empty */
    virtual void draw(Mtx* mtx);           /* fn_1_7124 GX line strip (direct FIFO writes on GC) */
};

} // namespace m531

#endif
