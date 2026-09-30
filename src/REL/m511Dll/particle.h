#ifndef M511_PARTICLE_H
#define M511_PARTICLE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"

namespace m511 {

class CPlayer;

class CStarGetEff : public CGameObject {
public:
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_8488 -> work->UpdateParticles */
    CStarGetEff(CPlayer* owner);                /* fn_1_84CC player UpdateCourse (a gate passed) */
    virtual ~CStarGetEff();                     /* fn_1_8770 Hu3DModelKill(m_id) */
    virtual void on_new_mode(int mode);         /* fn_1_87F8 */
    virtual void on_update();                   /* fn_1_8810 follow the owner; stop after 3 s */
    void InitParticle(HU3DPARTICLEDATA* data);  /* fn_1_894C also inlined in UpdateParticles */
    void UpdateParticles(Mtx mtx);              /* fn_1_8B8C deletes this when none is alive */

    HU3DMODELID m_id;         /* 0x10 Hu3DParticleCreate(CEffTex::m_starGetAnim, 8), stored last */
    HU3DPARTICLE* m_particle; /* 0x14 hookData; ->work = this */
    Vec m_pos;                /* 0x18 emitter = owner->m_pos */
    Vec m_rot;                /* 0x24 (0, owner->m_rotY, 0), write-only */
    CPlayer* m_owner;         /* 0x30 */
    float m_time;             /* 0x34 += 1/60 */
    bool m_stop;              /* 0x38 time > 3 */
    int m_frame;              /* 0x3C */
    int m_num;                /* 0x40 walked particles, 1..8 */
};

class CStarEff {
public:
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_8EF4 -> work->UpdateParticles */
    CStarEff(Vec* pos);                         /* fn_1_8F38 star ctor */
    ~CStarEff();                                /* fn_1_9128 Hu3DModelKill (from ~auto_ptr<CStarEff>) */
    void InitParticle(HU3DPARTICLEDATA* data);  /* fn_1_917C also inlined in UpdateParticles */
    void UpdateParticles(Mtx mtx);              /* fn_1_93BC */
    void SetPos(Vec* pos, Vec* rot);            /* fn_1_9700 CStarMan::on_update */

    HU3DMODELID m_id;         /* 0x00 Hu3DParticleCreate(CEffTex::m_starGetAnim, 40), stored last */
    HU3DPARTICLE* m_particle; /* 0x04 hookData; ->work = this */
    Vec m_pos;                /* 0x08 emitter */
    Vec m_rot;                /* 0x14 write-only */
    int m_unk20;              /* 0x20 0, write-only */
    int m_active;             /* 0x24 1, write-only */
};

} // namespace m511

#endif
