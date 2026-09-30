/* particle.h -- m501::CParticle (particle.cpp): the footprint model (drawn by CAsiatoMan) and the scoop
 * splash/burst particles. GC: CGameObject +0x00, empty CSingleton<CParticle> at +0x10, m_model +0x10;
 * size 0x14. particle.cpp does not include minigame.h. */
#ifndef M501_PARTICLE_H
#define M501_PARTICLE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"

namespace m501 {

class CParticle : public CGameObject, public CSingleton<CParticle> {
public:
    CParticle();
    virtual ~CParticle();
    virtual void on_new_mode(int mode);
    virtual void on_update();
    /* returns &ms_pointer->m_model (the footprint model), not the object */
    static CModel* getInstance();
    /* fn_1_A6C0 / fn_1_A768: a particle burst at pos tinted with flavour colour `color` (0..7);
     * called from CAisu (landing / take) */
    static void createSplash(Vec* pos, int color);
    static void createBurst(Vec* pos, int color);
    /* fn_1_A810 / fn_1_AAA4: HU3DPARTICLEHOOKs */
    static void splashHook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx);
    static void burstHook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx);

    CModel m_model; /* 0x10 data 0x3B0007, object "asiato" */
};

} // namespace m501

#ifndef __MWERKS__
template <> m501::CParticle* CSingleton<m501::CParticle>::ms_pointer; /* defined in asiato.cpp */
#endif

#endif
