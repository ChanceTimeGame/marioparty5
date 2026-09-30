#ifndef M511_BOATSPLASH_H
#define M511_BOATSPLASH_H

#include "REL/mgcpp/game.h"

namespace m511 {

class CBoatSplash {
public:
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_16E40 -> work->Update(mtx) */
    CBoatSplash();                                  /* fn_1_16E84 */
    ~CBoatSplash();                                 /* fn_1_170C8 Hu3DModelKill(m_particle) */
    void InitParticle(HU3DPARTICLEDATA* data, int i); /* fn_1_1711C also inlined in Update's respawn */
    void SetPos(Vec* pos, Vec* rot, float speed);   /* fn_1_17544 player UpdateMain */
    void Update(Mtx mtx);                           /* fn_1_1757C the particle state machine */

    HU3DMODELID m_particle;         /* 0x00 Hu3DParticleCreate(CEffTex::m_splashAnim, 32) */
    HU3DPARTICLE* m_particleData;   /* 0x04 hookData; ->work = this */
    Vec m_pos;                      /* 0x08 */
    Vec m_rot;                      /* 0x14 rot.y drives the emitter */
    Vec m_emitPos;                  /* 0x20 100 behind the boat, per (re)spawn */
    bool m_active;                  /* 0x2C respawn while set (the player writes it) */
    float m_speed;                  /* 0x30 SetPos */
};

class CBoatWake {
public:
    static void Hook(HU3DMODEL* model, Mtx* mtx); /* fn_1_17B94 -> Draw */
    CBoatWake();                                  /* fn_1_17BD8 layer 2, camera 0xF */
    ~CBoatWake();                                 /* fn_1_17CC8 Hu3DModelKill */
    void Start(Vec* pos, Vec* rot, float power);  /* fn_1_17D1C player UpdateMain */
    void Update();                                /* fn_1_17E6C t += 1/60; inactive at 0.5 */
    void Draw(Mtx* mtx);                          /* fn_1_17EC8 drawn only while active */

    HU3DMODELID m_model; /* 0x00 Hu3DHookFuncCreate(Hook), hookData = this */
    ANIMDATA* m_anim;    /* 0x04 CEffTex::m_wakeAnim (borrowed) */
    Vec m_pos;           /* 0x08 Start: 100 behind the boat */
    bool m_active;       /* 0x14 */
    float m_t;           /* 0x18 */
    float m_power;       /* 0x1C */
};

class CKibakoSplash {
public:
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_183C0 -> work->Update(mtx) */
    CKibakoSplash();             /* fn_1_18404 the particle init loop is inline */
    ~CKibakoSplash();            /* fn_1_187B0 Hu3DModelKill */
    void Start(Vec* pos);        /* fn_1_18804 kibako Break */
    void Update(Mtx mtx);        /* fn_1_1886C while started && !done */

    HU3DMODELID m_particle;       /* 0x00 Hu3DParticleCreate(CEffTex::m_splashAnim, 40), hidden */
    HU3DPARTICLE* m_particleData; /* 0x04 hookData; ->work = this */
    bool m_done;                  /* 0x08 no particle alive */
    bool m_started;               /* 0x09 */
};

} // namespace m511

#endif
