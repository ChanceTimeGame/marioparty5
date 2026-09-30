#ifndef M517_DUSTCLOUD_H
#define M517_DUSTCLOUD_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"

namespace m517 {

class CDustCloud : public CGameObject {
public:
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m); /* fn_1_1A4D4 -> Update */
    CDustCloud(const Vec* pos, GXColor col, int count); /* fn_1_1A518 (col by value: player copies it again per call) */
    virtual ~CDustCloud();                                            /* fn_1_1A678 */
    virtual void on_new_mode(int mode);                               /* fn_1_1A714 */
    void Update(Mtx m);                                               /* fn_1_1A72C deletes this when done */

    HU3DMODELID m_model;      /* 0x10 Hu3DParticleCreate(m_anim, count) */
    ANIMDATA* m_anim;         /* 0x14 0x4B0011 */
    HU3DPARTICLE* m_particle; /* 0x18 work = this */
};

class CDustPuff : public CGameObject {
public:
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m); /* fn_1_1AC90 -> Update */
    CDustPuff(const Vec* pos);                                        /* fn_1_1ACD4 */
    virtual ~CDustPuff();                                             /* fn_1_1AE48 */
    virtual void on_new_mode(int mode);                               /* fn_1_1AEE4 */
    void InitParticles(HU3DPARTICLE* p);                              /* fn_1_1AEFC (`this` unused) */
    void Update(Mtx m);                                               /* fn_1_1B220 deletes this when done */

    HU3DMODELID m_model;      /* 0x10 Hu3DParticleCreate(m_anim, 6) */
    ANIMDATA* m_anim;         /* 0x14 0x4B0011 */
    HU3DPARTICLE* m_particle; /* 0x18 */
};

} // namespace m517

#endif
