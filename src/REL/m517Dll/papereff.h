#ifndef M517_PAPEREFF_H
#define M517_PAPEREFF_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include <memory>

namespace m517 {

class CPaperEff : public CGameObject {
public:
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m); /* fn_1_13590 -> Update */
    CPaperEff(Vec* pos);                        /* fn_1_135D4 (unreferenced; inlined in CPaper()) */
    virtual ~CPaperEff();                       /* fn_1_1379C */
    virtual void on_new_mode(int mode);         /* fn_1_13838 */
    void InitParticle(HU3DPARTICLEDATA* p);     /* fn_1_13850 (unreferenced; inlined twice in Update) */
    void Update(Mtx m);                         /* fn_1_13A70 */
    void SetPos(Vec* pos);                      /* fn_1_13F44 (unreferenced) */
    void SetVel(Vec* vel);                      /* fn_1_13F60 (unreferenced) */

    HU3DMODELID m_model;      /* 0x10 Hu3DParticleCreate(m_anim, 10) */
    ANIMDATA* m_anim;         /* 0x14 0x4B0012 */
    HU3DPARTICLE* m_particle; /* 0x18 work = this */
    Vec m_pos;                /* 0x1C emitter (CPaper copies its position every update) */
    Vec m_vel;                /* 0x28 zeroed, never read */
};

class CPaperTex : public CSingleton<CPaperTex> {
public:
    enum { NUM_PLAYER = 4, NUM_CHAR = 13 };

    CPaperTex();                        /* fn_1_13F7C (gamemaster on_setup) */
    ~CPaperTex();                       /* fn_1_1415C (gamemaster; non-virtual) */
    ANIMDATA* GetFront(int idx);        /* fn_1_1424C (unreferenced; inlined in CPaper()) */
    ANIMDATA* GetBack(int idx);         /* fn_1_14258 (unreferenced; inlined in CPaper()) */

    ANIMDATA* m_front[NUM_PLAYER];      /* 0x00 0x4B0014 + 2 charNo (NULL for grp 0) */
    ANIMDATA* m_back[NUM_PLAYER];       /* 0x10 0x4B0015 + 2 charNo */
};

class CPaper : public CGameObject {
public:
    enum { MESH_N = 9 };

    static void DrawHook(HU3DMODEL* model, Mtx* mtx); /* fn_1_14268 -> Draw */
    CPaper(Vec* pos, Vec* target, Vec* rot, int idx); /* fn_1_142AC (player procOut) */
    virtual ~CPaper();                  /* fn_1_147F0 */
    virtual void on_new_mode(int mode); /* fn_1_14904 */
    virtual void on_update();           /* fn_1_1491C */
    void Draw(Mtx* view);
    void InitMesh();                    /* fn_1_14E6C */
    void Wave(int state);               /* fn_1_14F90 divides by m_target.y (800) */
    void DrawMesh(bool back);           /* fn_1_15104 GX_QUADS, 256 vertices */

    /* player procOut polls it */
    bool IsDone() const { return m_done; }

    HU3DMODELID m_model;          /* 0x010 Hu3DHookFuncCreate(DrawHook), layer 4 */
    ANIMDATA* m_front;            /* 0x014 CPaperTex::GetFront(idx) */
    ANIMDATA* m_back;             /* 0x018 */
    float m_time;                 /* 0x01C +1/60 */
    Vec m_pos;                    /* 0x020 */
    Vec m_target;                 /* 0x02C the gallery spot (y 800) */
    u8 m_unk38[12];               /* 0x038 never accessed */
    Vec m_unk44;                  /* 0x044 zeroed, never read */
    Vec m_rot;                    /* 0x050 only .y is read (Draw) */
    bool m_done;                  /* 0x05C arrived (player procOut) */
    Vec m_mesh[MESH_N][MESH_N];   /* 0x060 */
    u8 m_unk42C[0x30];            /* 0x42C never accessed */
    int m_state;                  /* 0x45C 0..3 */
    Vec m_size;                   /* 0x460 x = 2 bmp sizeX / 256 (width), z = height; y never accessed */
    int m_se;                     /* 0x46C PlaySe(0x6F3) (stopped in the dtor) */
    std::auto_ptr<CPaperEff> m_eff; /* 0x470 */
};

} // namespace m517

#ifndef __MWERKS__
template <> m517::CPaperTex* CSingleton<m517::CPaperTex>::ms_pointer; /* defined in effect.cpp (.bss 8) */
#endif

#endif
