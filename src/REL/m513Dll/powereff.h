#ifndef M513_POWEREFF_H
#define M513_POWEREFF_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include <memory>

namespace m513 {

class CPowerParticle : public CGameObject {
public:
    /* fn_1_8E78: the particle hook -> UpdateParticles */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m);
    CPowerParticle();                        /* fn_1_8EBC (unreferenced; inlined in CPowerEff()) */
    virtual ~CPowerParticle();               /* fn_1_9114 */
    void Start(Vec* pos);                    /* fn_1_91A8 (unreferenced) */
    void Stop();                             /* fn_1_9240 (unreferenced; inlined in CPowerEff::on_update) */
    virtual void on_new_mode(int mode);      /* fn_1_929C */
    void InitParticle(HU3DPARTICLEDATA* p);  /* fn_1_92B4 */
    void UpdateParticles(Mtx m);             /* fn_1_94E4 */
    void SetPos(Vec* pos);                   /* fn_1_9824 (unreferenced) */
    void SetVec(Vec* v);                     /* fn_1_9840 (unreferenced; m_vec is never read) */

    HU3DMODELID m_id;         /* 0x10 Hu3DParticleCreate(particle anim, 2) */
    HU3DPARTICLE* m_particle; /* 0x14 */
    Vec m_pos;                /* 0x18 emitter (CPowerEff copies its position every frame) */
    Vec m_vec;                /* 0x24 */
    bool m_active;            /* 0x30 */
};

class CPowerEff : public CGameObject {
public:
    /* fn_1_985C: Hu3D hook -> ((CPowerEff*)model->hookData)->Draw(*mtx) */
    static void DrawHook(HU3DMODEL* model, Mtx* mtx);
    CPowerEff();                             /* fn_1_98A0 */
    virtual ~CPowerEff();                    /* fn_1_9F20 */
    void Start(Vec* from, Vec* to, float delay); /* fn_1_9FE4 (player) */
    virtual void on_new_mode(int mode);      /* fn_1_A064 */
    virtual void on_update();                /* fn_1_A07C */
    void Draw(Mtx view);

    Vec m_pos;                                   /* 0x10 billboard centre */
    Vec m_target;                                /* 0x1C */
    HU3DMODELID m_hook;                          /* 0x28 Hu3DHookFuncCreate(DrawHook), killed in the dtor */
    GXColor m_color;                             /* 0x2A rgb 0xFF, a 0 */
    float m_time;                                /* 0x30 += 1/60 */
    int m_state;                                 /* 0x34 0..5 */
    float m_delay;                               /* 0x38 */
    std::auto_ptr<CPowerParticle> m_particle;    /* 0x3C */
    int m_frame;                                 /* 0x40 warp frame 0..31 */
    float m_scale;                               /* 0x44 eased to 1.5 */
};

} // namespace m513

#endif
