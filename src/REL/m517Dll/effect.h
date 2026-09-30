/* effect.h -- effect.cpp: the solo player's rolling ball and its sand trail (effect_input_dust.md §1-§2; names ours).
 * m517::CEffect: the sand trail, a CGameObject owning a 16-particle Hu3D particle model (anim 0x4B0011, colour
 * F0/E0/80, layer 2); CBall::Update calls the inlined Emit(pos) which restarts the next particle of the ring every 10
 * units of XZ travel (ring cursor = HU3DPARTICLE::dataCnt).
 * m517::CBall: the ball (model 0x4B0004 with shadow, radius 100) the solo steers with SetForce; quaternion rolling
 * (misc QuatRotArc), arena radius 600 - 100 with a wall bounce SE 0x6F4, a looping roll SE 0x6F2 whose volume follows
 * the speed; it owns its CEffect. HitPlayer (gamemaster's ForEachCross<CBall, CPlayer> callback) pushes a team player
 * out of the ball and calls CPlayer::Hit.
 * CEffect GC 0x34 (CBall() `li r3,0x34`): CGameObject +0 (vptr +8, m_execFlags +0xC), m_model +0x10, m_anim +0x14,
 * m_particle +0x18, m_emit +0x1C, m_vec +0x28. Vtable data_54 {~ 300, on_new_mode 39C, CGameObject::on_update 1E80}.
 * CBall GC 0xC0 (player `li r3,0xC0`): TLinkItem<CBall> +0 (ASet<CBall>::sm_ptr = effect.o .bss 0; no vptr), m_rot
 * +0x08, m_mtx +0x18, m_state +0x48 (PTMF, always null: no CBall PTMF constant exists), m_sphere +0x54 (pos, r = 100),
 * m_prevPos +0x64, m_vel +0x70, m_delta +0x7C, m_unk88 +0x88, m_unk94 +0x94, m_force +0xA0, m_idx +0xAC, m_wall
 * +0xB0, m_se +0xB4, m_model +0xB8, m_effect +0xBC. */
#ifndef M517_EFFECT_H
#define M517_EFFECT_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/om.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m517Dll/a_set.h"
#include <memory>

namespace m517 {

class CPlayer;

class CEffect : public CGameObject {
public:
    enum { NUM_PARTICLE = 16 };

    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m); /* fn_1_0 -> UpdateParticles */
    CEffect();                                  /* fn_1_44 (unreferenced; inlined in CBall()) */
    virtual ~CEffect();                         /* fn_1_300 */
    virtual void on_new_mode(int mode);         /* fn_1_39C */
    void InitParticle(HU3DPARTICLEDATA* p);     /* fn_1_3B4 (unreferenced; inlined in UpdateParticles) */
    void UpdateParticles(Mtx m);                /* fn_1_5AC */
    void Emit(const Vec* pos);                  /* fn_1_8A4 (unreferenced; inlined in CBall::Update) */
    void SetVec(const Vec* v);                  /* fn_1_9D0 (unreferenced; m_vec is never read) */

    HU3DMODELID m_model;      /* 0x10 Hu3DParticleCreate(m_anim, 16) */
    ANIMDATA* m_anim;         /* 0x14 0x4B0011 (locked; killed in the dtor) */
    HU3DPARTICLE* m_particle; /* 0x18 Hu3DData[m_model].hookData; work = this */
    Vec m_emit;               /* 0x1C last emit position (XZ; y 0) */
    Vec m_vec;                /* 0x28 not initialised, never read */
};

/* fn_1_9EC (unreferenced; inlined in CBall::HitPlayer): pushes `pos` and the sphere apart to 130 + s->r; the
 * sphere moves by (1 - w) of the overlap, pos by w. File scope, external linkage (name ours). */
bool PushOut(Vec* pos, CSphere* s, float w);

class CBall : public TLinkItem<CBall> {
public:
    typedef void (CBall::*ProcFunc)();

    /* by value: the ctor's null PTMF store goes through a stack temporary (B58 FD0..1004) */
    void setState(ProcFunc state) { m_state = state; }

    CBall(int idx);                         /* fn_1_B58 (player) */
    ~CBall();                                /* fn_1_10F8 */
    void SetPos(const Vec* pos);             /* fn_1_11A8 pos + (0, 100, 0) */
    float GetSpeedRatio();                   /* fn_1_12E8 |vel| / (700 / 60) (input, player) */
    void GetQuat(Quaternion* q);             /* fn_1_1360 (unreferenced) */
    void SetForce(const Vec* f);             /* fn_1_1384 (player) */
    void Stop();                             /* fn_1_13A0 (player) */
    void Update();                           /* fn_1_13D4 PTMF gamemaster data_380 */
    void ClampVelXZ(float lim);              /* fn_1_164C (unreferenced; inlined in Move) */
    void Move();                             /* fn_1_16F8 */
    void Roll(const Vec* from, const Vec* to); /* fn_1_1904 (also player) */
    void CollideStage();                     /* fn_1_1A44 */
    static void HitBall(CBall* a, CBall* b);      /* fn_1_1C78 (unreferenced) */
    static void HitPlayer(CBall* ball, CPlayer* p); /* fn_1_1CEC gamemaster ForEachCross<CBall, CPlayer> */

    /* read across units (input, player) */
    Vec* GetPos() { return &m_sphere.pos; }
    Vec* GetDelta() { return &m_delta; }
    /* Roll's radius read (the inline's result temporary: 1964 fmr) */
    float GetRadius() const { return m_sphere.r; }

    /* 0x00 CLinkNode (TLinkItem), on ASet<CBall> */
    Quaternion m_rot;          /* 0x08 (0, 0, 0, 1) */
    Mtx m_mtx;                 /* 0x18 PSMTXQuat(m_rot), copied into the model matrix */
    ProcFunc m_state;          /* 0x48 __ptmf_null (12 bytes on CW); never set */
    CSphere m_sphere;
    Vec m_prevPos;
    Vec m_vel;                 /* 0x70 x, "fall speed" y, z */
    Vec m_delta;               /* 0x7C pos - prevPos of the last Update (input 984C) */
    Vec m_unk88;               /* 0x88 zeroed by the ctor only */
    Vec m_unk94;               /* 0x94 zeroed by the ctor and SetPos */
    Vec m_force;               /* 0xA0 SetForce; x0.3 in Move; zeroed every Update */
    int m_idx;                 /* 0xAC ctor argument (unused) */
    bool m_wall;               /* 0xB0 touching the wall (bounce SE latch) */
    int m_se;                  /* 0xB4 roll SE 0x6F2 (stopped in the dtor) */
    CModel m_model;            /* 0xB8 0x4B0004 (member: ~CModel(-1)) */
    std::auto_ptr<CEffect> m_effect; /* 0xBC */
};

} // namespace m517

#ifndef __MWERKS__
template <> ASet<m517::CBall>* ASet<m517::CBall>::sm_ptr; /* defined in effect.cpp (.bss 0) */
#endif

#endif
