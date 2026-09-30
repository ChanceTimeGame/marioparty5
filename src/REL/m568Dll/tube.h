#ifndef M568_TUBE_H
#define M568_TUBE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/om.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m568Dll/a_set.h"

namespace m568 {

class CObstacle;

class CTube : public TLinkItem<CTube> {
public:
    typedef void (CTube::*StateFunc)();

    /* fn_1_11F6C (unreferenced; inlined into the ctor with its own jumptable): cid 0..8 -> 0x7B0007 + cid,
     * 9..12 -> 0x7B0010, else assert(!"invalid cid") tube.cpp:53 and 0 */
    static u32 GetModelId(int cid);
    CTube(int isTeam, int cid);                /* fn_1_12058 m_isSolo = (isTeam == 0) */
    ~CTube();                                  /* fn_1_123DC */
    void Reset(const Vec* pos);                /* fn_1_12448 */
    void GetRot(Quaternion* q);                /* fn_1_1262C */
    void AddSteer(const Vec* v);               /* fn_1_12650 */
    void Brake();                              /* fn_1_1268C (inlined into update) */
    void GetNormPos(Vec* out);                 /* fn_1_1284C (unreferenced) */
    void Stop();                               /* fn_1_1289C */
    void update();                             /* fn_1_1290C PTMF (game_master data_2D8) */
    void stateSlide();                         /* fn_1_12D10 PTMF data_6F8 */
    void stateBlown();                         /* fn_1_12D84 PTMF data_768 */
    void SetTargetUp(const Vec* n);            /* fn_1_12E80 (unreferenced; inlined 3x) |n.x| <= sin 6deg */
    void ApplySteer(const Vec* n);             /* fn_1_12F28 (unreferenced; inlined) */
    void CollideGround();                      /* fn_1_12FD8 */
    float CollideNormal(const Vec* n, const Vec* v); /* fn_1_133FC */
    void WallCheck();                          /* fn_1_134D4 */
    void ApplyGravity();                       /* fn_1_13634 */
    void Damp(float k);                        /* fn_1_136CC (unreferenced) */
    bool WallProbe(const Vec* local);          /* fn_1_1375C */
    void ApplyForce();                         /* fn_1_13994 */
    static void GravityPart(Vec* out, const Vec* v); /* fn_1_13A30 (unreferenced; inlined) */
    void ClampLateral(float max);              /* fn_1_13A90 (unreferenced; inlined 2x with 25) */
    void Integrate();                          /* fn_1_13B54 */
    void UpdateMatrix();                       /* fn_1_13DE4 */
    void LocalToWorld(Vec* dst, const Vec* src); /* fn_1_13ECC */
    static void CollideTubes(CTube* a, CTube* b);
    void HitObstacle(CObstacle* o);
    bool TakeEvent();                          /* fn_1_14208 (drives the pad rumble) */
    void KnockOut(CTube* by);                  /* fn_1_14238 `by` unused */
    void PlayVoice();                          /* fn_1_143F4 */
    void StopVoice();                          /* fn_1_14448 */

    /* by value (retail copies the PTMF constant to a stack temporary first) */
    void setState(StateFunc s) { m_state = s; }
    /* const inline accessors: retail's `lbz; clrlwi; cmplwi` reads of +0x08 / +0xB8 (lead relay, F5 proof) */
    bool IsSolo() const { return m_isSolo; }
    bool IsOut() const { return m_out; }
    const CSphere* GetSphere() const { return &m_sphere; }
    /* Reset writes the position through it (addi + mr, then component stores) */
    Vec* GetPos() { return &m_sphere.pos; }

    bool m_isSolo;       /* 0x08 */
    int m_no;            /* 0x0C solo 0, team 1..3 (game_master on_setup) */
    Vec m_up;            /* 0x10 lerps toward m_targetUp (0.09 a frame) */
    Vec m_targetUp;      /* 0x1C */
    Quaternion m_rot;    /* 0x28 rotArc((0,1,0), m_up) */
    Mtx m_mtx;           /* 0x38 */
    StateFunc m_state;   /* 0x68 (12 bytes on CW) */
    CSphere m_sphere;    /* 0x74 pos, r (0x80) = solo ? 135 : 100 */
    Vec m_prevPos;       /* 0x84 */
    Vec m_vel;           /* 0x90 */
    Vec m_impulse;       /* 0x9C */
    Vec m_force;         /* 0xA8 */
    float m_mass;        /* 0xB4 solo ? 30 : 2 */
    bool m_out;          /* 0xB8 knocked out */
    int m_event;         /* 0xBC 2 = hard landing / knockout, 8 = obstacle bump (TakeEvent) */
    int m_voiceSe;       /* 0xC0 -1 = none */
    int m_loopSe;        /* 0xC4 solo: HuAudFXPlay(0x90C), else -1 */
    Vec m_steer;         /* 0xC8 */
    CModel m_model;      /* 0xD4 */
};

} // namespace m568

#ifndef __MWERKS__
template <> ASet<m568::CTube>* ASet<m568::CTube>::sm_ptr; /* defined in input.cpp */
#endif

#endif
