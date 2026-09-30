#ifndef M511_WATER_H
#define M511_WATER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m511 {

class CWater : public CGameObject, public CSingleton<CWater> {
public:
    enum { MESH = 16 };

    static void Hook(HU3DMODEL* model, Mtx* mtx); /* fn_1_19804 ((CWater*)hookData)->Draw(mtx) */
    CWater();                                     /* fn_1_19848 */
    virtual ~CWater();                            /* fn_1_19A74 */
    void InitMesh();                              /* fn_1_19B58 */
    void UpdateMesh();                            /* fn_1_19D18 the spring step + colours */
    void AddWave(const Vec* pos, float dv);       /* fn_1_19FC8 unreferenced (inlined with -0.5 in on_update) */
    float GetHeight(const Vec* pos);              /* fn_1_1A150 bilinear surface height */
    Vec GetNormal(const Vec* pos);                /* fn_1_1A394 struct return */
    virtual void on_new_mode(int mode);           /* fn_1_1A518 */
    virtual void on_update();                     /* fn_1_1A530 */
    void Draw(Mtx* mtx);                          /* fn_1_1A8C0 GX state, DrawMesh, DrawGlare */
    void DrawMesh();                              /* fn_1_1A9EC 15x15 QUADS, POS + CLR0 + TEX0 */
    void DrawGlare(Mtx* mtx);                     /* fn_1_1B0CC one QUAD, POS + TEX0, additive */

    ANIMDATA* m_surfaceAnim;      /* 0x0010 0x450021 -> TEXMAP0 */
    ANIMDATA* m_glareAnim;        /* 0x0014 0x45002B -> TEXMAP1 */
    HU3DMODELID m_model;          /* 0x0018 Hu3DHookFuncCreate(Hook), layer 3, camera 0xF */
    float m_time;                 /* 0x001C += 1/60 */
    int m_frame;                  /* 0x0020 every 64th: a random drop */
    int m_unk24;                  /* 0x0024 never accessed */
    Vec m_meshPos[MESH][MESH];    /* 0x0028 x = 1600 j - 12800, z = 1600 i - 12800; y = height */
    Vec m_meshUV[MESH][MESH];     /* 0x0C28 .x = j / 16, .z = i / 16 */
    float m_meshVel[MESH][MESH];  /* 0x1828 */
    float m_meshPrev[MESH][MESH]; /* 0x1C28 height snapshot per step */
    GXColor m_meshCol[MESH][MESH];/* 0x2028 grey from the height, alpha 0xB4 */
    Vec m_scroll;                 /* 0x2428 texture scroll */
};

class CWaterRipple : public CGameObject {
public:
    enum { NUM_PATCH = 80 };

    static void Hook(HU3DMODEL* model, Mtx* mtx); /* fn_1_1B534 -> Draw */
    CWaterRipple();                               /* fn_1_1B578 the patch init is inline */
    virtual ~CWaterRipple();                      /* fn_1_1BAD0 */
    virtual void on_new_mode(int mode);           /* fn_1_1BB68 */
    virtual void on_update();                     /* fn_1_1BB80 */
    void Draw(Mtx* mtx);                          /* fn_1_1BC84 GX state (indirect warp) */
    void DrawPatches();                           /* fn_1_1BD9C <= 80 QUADS within 8000 of the eye */

    ANIMDATA* m_anim;         /* 0x10 0x450022 -> MAP0 */
    ANIMDATA* m_warpAnim;     /* 0x14 0x45002F -> MAP1 (indirect) */
    HU3DMODELID m_model;      /* 0x18 layer 1, camera 0xF */
    float m_time;             /* 0x1C */
    Vec m_scroll;             /* 0x20 */
    Vec m_patch[NUM_PATCH];   /* 0x2C y = -350 */
};

class CWaterRing : public CGameObject {
public:
    enum { NUM_VTX = 32 };

    static void Hook(HU3DMODEL* model, Mtx* mtx); /* fn_1_1C2E0 -> Draw */
    CWaterRing(const Vec* pos);                   /* fn_1_1C324 unreferenced */
    virtual ~CWaterRing();                        /* fn_1_1C45C */
    void InitRing();                              /* fn_1_1C4F4 */
    virtual void on_new_mode(int mode);           /* fn_1_1C640 */
    virtual void on_update();                     /* fn_1_1C658 GetHeight inlined (singleton.h:39) */
    void Draw(Mtx* mtx);                          /* fn_1_1C9EC 16 QUADS, POS + CLR0 + TEX0, indirect */

    ANIMDATA* m_tex;          /* 0x010 0x45002C */
    ANIMDATA* m_warpAnim;     /* 0x014 0x45002F */
    HU3DMODELID m_model;      /* 0x018 layer 3 */
    float m_time;             /* 0x01C */
    Vec m_scroll;             /* 0x020 */
    Vec m_ring[NUM_VTX];      /* 0x02C radius 550 even / 800 odd */
    Vec m_pos;                /* 0x1AC y = water height + 30 */
};

} // namespace m511

#ifndef __MWERKS__
template <> m511::CWater* CSingleton<m511::CWater>::ms_pointer; /* defined in boat.cpp (.bss 1C) */
#endif

#endif
