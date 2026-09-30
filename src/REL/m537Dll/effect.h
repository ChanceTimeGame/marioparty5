#ifndef M537_EFFECT_H
#define M537_EFFECT_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m537 {

class CEffect : public CGameObject, public CSingleton<CEffect> {
public:
    enum { NUM_ANIM = 4, NUM_FLARE = 8 };

    static void DrawHook(HU3DMODEL* model, Mtx* mtx); /* fn_1_7254 GetInstancePtr()->Draw(mtx) (no assert) */
    CEffect();                                        /* fn_1_72A0 */
    virtual ~CEffect();                               /* fn_1_74C0 */
    virtual void on_new_mode(int mode);               /* fn_1_75B8 */
    void LoadTex();                                   /* fn_1_75D0 (unreferenced; inlined in Draw) */
    void Draw(Mtx* mtx);                              /* fn_1_764C */
    void DrawFlare(float alpha, Vec pos, float size, u32 color, int tex); /* fn_1_7DBC `this` unused; Vec by value (copy-to-temp) */
    Vec Project(Vec p, Mtx* mtx);                     /* fn_1_81AC its result only feeds two dead stores */
    virtual void on_update() {}                       /* fn_1_83C8 */

    ANIMDATA* m_anim[NUM_ANIM]; /* 0x10 0x5F0019..1C, locked */
};

} // namespace m537

#ifndef __MWERKS__
template <> m537::CEffect* CSingleton<m537::CEffect>::ms_pointer; /* defined in effect.cpp (bss 9F8) */
#endif

#endif
