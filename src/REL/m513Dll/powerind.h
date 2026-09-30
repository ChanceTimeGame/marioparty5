#ifndef M513_POWERIND_H
#define M513_POWERIND_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m513 {

class CPowerInd : public CGameObject, public CSingleton<CPowerInd> {
public:
    enum { SCREEN_W = 640, SCREEN_H = 480, WARP_NUM = 32 };

    static void CopyHook(HU3DMODEL* model, Mtx* mtx);
    CPowerInd();                          /* fn_1_AE58 */
    virtual ~CPowerInd();                 /* fn_1_B110 kills the 36 anims (retail: not the hook) */
    virtual void on_new_mode(int mode);   /* fn_1_B23C */
    virtual void on_update();             /* fn_1_B254 m_vec += 0.003 (unused) */
    void InitTexObj();                    /* fn_1_B2AC */
    void CopyEFB();                       /* fn_1_B338 (unreferenced; inlined in CopyScreen) */
    void SetProjTexGen(Mtx m);            /* fn_1_B390 (unreferenced; inlined in CopyScreen) */
    void CopyScreen(Mtx m);               /* fn_1_B458 */
    /* inline accessors: the effects read the texture bank through these (retail: a `this` copy and a return temp
     * per call -- powereff 8EBC / 98A0 / A528, taimatsu 6D50, leaf 77E8 / 85F4); they emit nothing unless used.
     * GetFireAnim / GetLeafAnim: F5's spelling (taimatsu / leaf) */
    GXTexObj* GetTexObj() { return &m_texObj; }
    ANIMDATA* GetMask() { return m_mask; }
    ANIMDATA* GetWarp(int frame) { return m_warp[frame]; }
    ANIMDATA* GetParticleAnim() { return m_particleAnim; }
    ANIMDATA* GetFireAnim() { return m_fireAnim; }
    ANIMDATA* GetLeafAnim() { return m_leafAnim; }

    u8 m_unk10[0x20];         /* 0x10 never referenced (guess: an unused second GXTexObj) */
    GXTexObj m_texObj;        /* 0x30 over m_buf, 640x480 RGB565, clamp, no mip */
    u8 m_buf[SCREEN_W * SCREEN_H * 2] ATTRIBUTE_ALIGN(32); /* 0x60 the EFB copy */
    Vec m_vec;                /* 0x96060 += 0.003 per frame, never read */
    ANIMDATA* m_warp[WARP_NUM]; /* 0x9606C 0x470019 + i */
    ANIMDATA* m_mask;         /* 0x960EC 0x470015 power-ball mask */
    ANIMDATA* m_particleAnim; /* 0x960F0 0x470016 CPowerParticle */
    ANIMDATA* m_fireAnim;     /* 0x960F4 0x470017 CTaimatsu */
    ANIMDATA* m_leafAnim;     /* 0x960F8 0x470018 CLeafEffect */
};

} // namespace m513

#ifndef __MWERKS__
template <> m513::CPowerInd* CSingleton<m513::CPowerInd>::ms_pointer; /* defined in input.cpp */
#endif

#endif
