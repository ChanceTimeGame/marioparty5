#ifndef M511_STAR_H
#define M511_STAR_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/m511Dll/particle.h"
#include <memory>

namespace m511 {

class CStarRing {
public:
    enum { NUM_VTX = 48 };

    static void DrawHook(HU3DMODEL* model, Mtx* mtx); /* fn_1_DF2C -> Draw */
    CStarRing();                                      /* fn_1_DF70 */
    ~CStarRing();                                     /* fn_1_E060 Hu3DModelKill */
    void Init();                                      /* fn_1_E0B4 the 48 vertices + alphas */
    void Update();                                    /* fn_1_E220 scroll += 1/60, wraps at 1 */
    void Draw(Mtx* mtx);                              /* fn_1_E268 */
    void SetPos(Vec* pos) { m_pos = *pos; }           /* inline (CStarMan()): the column under a star */

    HU3DMODELID m_model;      /* 0x000 Hu3DHookFuncCreate(DrawHook), layer 5, camera 0xF */
    ANIMDATA* m_anim;         /* 0x004 CEffTex::m_ringAnim (borrowed) */
    Vec m_pos;                /* 0x008 star pos, y - 300 (set by CStarMan) */
    float m_yScale;           /* 0x014 1.0 */
    u8 m_alpha[NUM_VTX];      /* 0x018 0x80 for the lower two rings, 0 on top */
    Vec m_vtx[NUM_VTX];       /* 0x048 */
    float m_scroll;           /* 0x288 */
};

class CStarMan : public CGameObject, public CSingleton<CStarMan> {
public:
    enum { NUM_STAR = 5 };

    CStarMan();                         /* fn_1_D318 */
    virtual ~CStarMan();                /* fn_1_D948 */
    static void GetPos(int gate, Vec* out); /* fn_1_DAB8 player, kibako, staryaji */
    virtual void on_update();           /* fn_1_DB04 */
    virtual void on_new_mode(int mode); /* fn_1_DF04 */

    int m_hits[NUM_STAR];                        /* 0x10 players that took star i (player ++) */
    int m_phase[NUM_STAR];                       /* 0x24 spin phase */
    int m_pop[NUM_STAR];                         /* 0x38 pop timer (player sets 18) */
    CModel m_star;                               /* 0x4C 0x450016 */
    HU3DMODELID m_starMdl[NUM_STAR];             /* 0x4E [0] = m_star, [1..4] Hu3DModelLink */
    CModel m_mark0;                              /* 0x58 0x450017 */
    CModel m_mark1;                              /* 0x5A 0x450018 */
    CModel m_mark2;                              /* 0x5C 0x450019 */
    CModel m_mark3;                              /* 0x5E 0x45001A */
    CModel m_mark4;                              /* 0x60 0x45001B */
    std::auto_ptr<CStarRing> m_ring[NUM_STAR];   /* 0x64 */
    HU3DMODELID m_markMdl[NUM_STAR];             /* 0x78 copies of the five marker ids */
    int m_frame;                                 /* 0x84 never read */
    float m_yaw;                                 /* 0x88 marker yaw, += 2 */
    std::auto_ptr<CStarEff> m_eff[NUM_STAR];     /* 0x8C */
};

} // namespace m511

#ifndef __MWERKS__
template <> m511::CStarMan* CSingleton<m511::CStarMan>::ms_pointer; /* defined in gamemaster.cpp (.bss A2C) */
#endif

#endif
