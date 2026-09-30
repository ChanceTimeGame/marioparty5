#ifndef M513_TAIMATSU_H
#define M513_TAIMATSU_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"

namespace m513 {

class CTaimatsu : public CGameObject {
public:
    /* fn_1_6D0C: the particle hook -> UpdateParticles */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m);
    CTaimatsu(Vec* pos);                    /* fn_1_6D50 */
    virtual ~CTaimatsu();                   /* fn_1_6F78 */
    virtual void on_new_mode(int mode);     /* fn_1_700C */
    virtual void on_update();               /* fn_1_7024 */
    void InitParticle(HU3DPARTICLEDATA* p); /* fn_1_7078 (unreferenced; inlined in UpdateParticles) */
    void UpdateParticles(Mtx m);            /* fn_1_72AC */

    HU3DMODELID m_id;         /* 0x10 */
    HU3DPARTICLE* m_particle; /* 0x14 ->work = this */
    float m_time;             /* 0x18 += 1/60, never read */
    int m_frame;              /* 0x1C */
    int m_count;              /* 0x20 live particles 1..16 */
};

} // namespace m513

#endif
