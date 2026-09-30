#ifndef M579_EFFECT_H
#define M579_EFFECT_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/tlink.h"

namespace m579 {

class CEffect : public CGameObject, public CSingleton<CEffect> {
public:
    CEffect();                          /* fn_1_BA70 */
    virtual ~CEffect();                 /* fn_1_BC00 CSplash::DeleteAll, HuSprAnimKill(s_anim) */
    virtual void on_new_mode(int mode); /* fn_1_BCE0 (= m501) */
    virtual void on_update();           /* fn_1_BCF8 CSplash::UpdateAll (= m512 7B2C) */

    static ANIMDATA* s_anim;            /* bss A9C 0x850003 (locked) */
};

class CSplash : public TLinkItem<CSplash> {
public:
    CSplash(Vec* pos, int type);        /* fn_1_BD18 type 0 small (+ ripple 200), else big (+ ripple 400) */
    ~CSplash();                         /* fn_1_BED0 Hu3DModelKill(m_id) (= m536 779C) */
    static void DeleteAll();            /* fn_1_BF38 (= m536 7804) */
    static void UpdateAll();            /* fn_1_C008 (= m512 7DAC) */
    static void Update(CSplash* s);     /* fn_1_C038 delete after 64 frames */
    static void HookSmall(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_C0A0 r 10, y0 10 */
    static void HookBig(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx);   /* fn_1_C2F0 r 30, y0 15 */

    static TLinkList<CSplash> s_list;   /* bss AAC; its DestructorChain AA0 */

    s16 m_id;     /* 0x08 Hu3DParticleCreate(s_anim, 32) */
    int m_frame;  /* 0x0C */
};

} // namespace m579

#ifndef __MWERKS__
template <> m579::CEffect* CSingleton<m579::CEffect>::ms_pointer; /* defined in puku2.cpp (bss A04) */
#endif

#endif
