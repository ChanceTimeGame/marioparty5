#ifndef M537_WATER_H
#define M537_WATER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"

namespace m537 {

class CMist : public CGameObject {
public:
    CMist(const Vec* pos, const Vec* rot);   /* fn_1_125AC (unreferenced; inlined 3x in the CWater ctor) */
    virtual ~CMist();                        /* fn_1_126C8 */
    virtual void on_new_mode(int mode);      /* fn_1_12758 */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_12770 */

    s16 m_particle;   /* 0x10 Hu3DParticleCreate(anim, 32) */
    ANIMDATA* m_anim; /* 0x14 0x5F0018 (locked) */
};

class CSplash : public CGameObject {
public:
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_12C3C ((CSplash*)work)->Update */
    CSplash(const Vec* pos);                 /* fn_1_12C80 (center_obj; inlined in Splash) */
    virtual ~CSplash();                      /* fn_1_12DD4 */
    virtual void on_new_mode(int mode);      /* fn_1_12E64 */
    void Update(Mtx mtx);

    s16 m_particle;                /* 0x10 Hu3DParticleCreate(anim, 32) */
    ANIMDATA* m_anim;              /* 0x14 0x5F0017 */
    HU3DPARTICLE* m_particleData;  /* 0x18 Hu3DData[m_particle].hookData; its work = this */
};

class CSplashModel : public CGameObject, public CModel {
public:
    CSplashModel(const Vec* pos);            /* fn_1_13294 (center_obj; inlined in Splash) */
    virtual ~CSplashModel();                 /* fn_1_133A8 */
    virtual void on_update();                /* fn_1_13434 delete this at motion end */
    virtual void on_new_mode(int mode);      /* fn_1_134C0 */
    /* 0x10 CModel base (0x5F0013) */
};

class CWater : public CGameObject, public CSingleton<CWater> {
public:
    enum { SCREEN_W = 640, SCREEN_H = 480, MESH_N = 32, WARP_N = 32, NUM_TAKI = 3, NUM_MIST = 3 };

    static void Hook(HU3DMODEL* model, Mtx* mtx);
    CWater(s16 stageModel);                  /* fn_1_13524 */
    virtual ~CWater();                       /* fn_1_1393C */
    void InitTaki();                         /* fn_1_13A44 */
    void InitMesh();                         /* fn_1_13AC8 */
    void UpdateMesh();
    void AddForce(const Vec* p, float dy);   /* fn_1_14414 (dorrie UpdateRipple) */
    float GetHeight(const Vec* p);           /* fn_1_145A0 (player procFloat) */
    void Splash(const Vec* p, float dy);     /* fn_1_14764 (player procFall) */
    void UpdateWarpTex();
    void DrawTakiAll(Mtx* mtx);              /* fn_1_14DB0 (unreferenced; inlined in Draw) */
    void DrawTaki(Mtx* mtx, HSFOBJECT* obj);
    void LoadTextures();                     /* fn_1_15300 (unreferenced; inlined in Draw) the EFB copy (§4.1) */
    void InitTexObj();                       /* fn_1_153D4 */
    void SetProjTexGen(Mtx* mtx);            /* fn_1_154C8 (unreferenced; inlined in Draw; m513 powerind) */
    virtual void on_new_mode(int mode);      /* fn_1_1557C */
    virtual void on_update();                /* fn_1_15594 */
    void Draw(Mtx* mtx);                     /* fn_1_15A48 */
    void DrawMesh();

    GXTexObj m_copyTex;           /* 0x10 over m_copyBuf, 640x480 RGB565, clamp */
    GXTexObj m_warpTex;           /* 0x30 over m_warpBuf, 32x32 IA8, repeat */
    u8 m_copyBuf[SCREEN_W * SCREEN_H * 2] ATTRIBUTE_ALIGN(32); /* 0x60 the EFB copy */
    ANIMDATA* m_takiWarpAnim;     /* 0x96060 0x5F0016 -> TEXMAP2 */
    ANIMDATA* m_surfaceAnim;      /* 0x96064 0x5F0015 -> TEXMAP3 */
    ANIMDATA* m_takiAnim;         /* 0x96068 0x5F0014 -> TEXMAP4 */
    Vec m_scroll;                 /* 0x9606C y = -0.5 * time */
    HSFOBJECT* m_taki[NUM_TAKI];  /* 0x96078 "taki_a/b/c" of m_model */
    s16 m_stageModel;             /* 0x96084 the ctor argument (write-only) */
    s16 m_model;                  /* 0x96086 0x5F0012 (hidden; the waterfalls' data source) */
    float m_time;                 /* 0x96088 seconds */
    int m_se;                     /* 0x9608C HuAudFXPlay(0x7D8) (looped; stopped in the dtor) */
    u8 m_warpBuf[WARP_N * WARP_N * 2] ATTRIBUTE_ALIGN(32); /* 0x960A0 IA8, GX 4x4-tiled */
    Vec m_meshPos[MESH_N][MESH_N];     /* 0x968A0 rest (200x - 3200, 0, 200y - 3200) */
    Vec m_meshVel[MESH_N][MESH_N];     /* 0x998A0 */
    Vec m_meshUV[MESH_N][MESH_N];      /* 0x9C8A0 (x / 32, -, y / 32) in .x / .z */
    GXColor m_meshCol[MESH_N][MESH_N]; /* 0x9F8A0 */
};

class CRipple : public CGameObject {
public:
    static void Hook(HU3DMODEL* model, Mtx* mtx); /* fn_1_169F8 ((CRipple*)hookData)->Draw(mtx) */
    CRipple(const Vec* pos);                 /* fn_1_16A3C */
    virtual ~CRipple();                      /* fn_1_16B48 */
    virtual void on_new_mode(int mode);      /* fn_1_16BD8 */
    virtual void on_update();                /* fn_1_16BF0 */
    void Draw(Mtx* mtx);

    s16 m_model;      /* 0x10 Hu3DHookFuncCreate(Hook), hookData = this */
    ANIMDATA* m_anim; /* 0x14 0x5F001D */
    Vec m_pos;        /* 0x18 y = the water height each frame */
    float m_t;        /* 0x24 0 -> 1 over 60 frames, then wraps to 0 */
};

} // namespace m537

#ifndef __MWERKS__
template <> m537::CWater* CSingleton<m537::CWater>::ms_pointer; /* defined in dorrie.cpp (bss 9F0) */
#endif

#endif
