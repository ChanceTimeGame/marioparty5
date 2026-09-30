#ifndef M511_EFFRING_H
#define M511_EFFRING_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m511 {

class CEffRing : public CGameObject, public CSingleton<CEffRing> {
public:
    enum { NUM_ANIM = 4, NUM_FLARE = 8 };

    static void DrawHook(HU3DMODEL* model, Mtx* mtx); /* fn_1_6B0C GetInstancePtr()->Draw(mtx) (no assert) */
    CEffRing();                                       /* fn_1_6B58 unreferenced */
    virtual ~CEffRing();                              /* fn_1_6D50 */
    virtual void on_new_mode(int mode);               /* fn_1_6E48 */
    void LoadTex();                                   /* fn_1_6E60 unreferenced (inlined in Draw) */
    void Draw(Mtx* mtx);                              /* fn_1_6EDC */
    void DrawFlare(float alpha, Vec pos, float size, u32 color, int tex); /* fn_1_7654 */
    Vec Project(Vec p, Mtx* mtx);                     /* fn_1_7A44 */
    virtual void on_update() {}                       /* fn_1_7C74 */

    ANIMDATA* m_anim[NUM_ANIM]; /* 0x10 0x450023..26, locked */
    Vec m_pos;                  /* 0x20 the sun (0, 500, 500) */
};

} // namespace m511

#ifndef __MWERKS__
template <> m511::CEffRing* CSingleton<m511::CEffRing>::ms_pointer; /* defined in effring.cpp (.bss A10) */
#endif

#endif
