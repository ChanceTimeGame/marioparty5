#ifndef M532_BALL_H
#define M532_BALL_H

#include "REL/m532Dll/config.h"
#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/m532Dll/man_object.h"
#include <memory>

namespace m532 {

class CBallMan : public CGameObject, public CSingleton<CBallMan> {
public:
    CBallMan();                              /* fn_1_0 */
    virtual ~CBallMan();                     /* fn_1_370 key function */
    /* fn_1_454 (unreferenced; inlined into both ball ctors): the master of kind & 3, motion reset and paused */
    static CModel* GetModel(int kind);
    static s16 GetUnk20();                   /* fn_1_50C unreferenced: m_unk20 */
    static void LoadRopeTex();               /* fn_1_57C unreferenced; inlined into CHangBall::draw */
    virtual void on_new_mode(int mode) { m_execFlags &= ~(1 << mode); } /* fn_1_1B00 weak */

    std::auto_ptr<CModel> m_model[4];        /* 0x10 masters 0x5A0005..8, hidden (setAttr(1)) */
    s16 m_unk20;                             /* 0x20 -1; only read by GetUnk20 (purpose unknown) */
    ANIMDATA* m_ropeAnim;                    /* 0x24 0x5A0009; never freed (retail R1) */
};

class CHangBall : public CObject {
public:
    CHangBall(float angleOfs, int index);    /* fn_1_604 */
    virtual ~CHangBall();                    /* fn_1_86C */
    /* fn_1_8DC (man_map grabNearest): once only -- hides the ball, SE 0x7AC, launches a CBall at `target`;
     * returns its handle (0 when already shot) */
    int Shoot(Vec* target);
    Vec* GetPos();                           /* fn_1_984 */
    u8 IsShot();                             /* fn_1_98C u8: `lbz; clrlwi` (m501 isTaken, m531 IsDone) */
    virtual void update();                   /* fn_1_998 */
    void CalcPivot();                        /* fn_1_9F8 (inlined into Move) */
    void Move();                             /* fn_1_AEC pendulum */
    void Orient();
    virtual void draw(Mtx* mtx);             /* fn_1_EF0 the rope, one textured GX_LINES segment */

    CModel m_model;                          /* 0x14 link copy of master index & 3; layer 4 */
    float m_angleOfs;                        /* 0x18 degrees on the ring */
    int m_index;                             /* 0x1C model kind & 3, star phase * 45 */
    bool m_shot;                             /* 0x20 */
    Vec m_pivot;                             /* 0x24 rope pivot (recomputed every frame) */
    Vec m_attach;                            /* 0x30 rope end on the ball */
    Vec m_pos;                               /* 0x3C */
    Vec m_vel;                               /* 0x48 */
    float* m_spinPtr;
    float m_spin;                            /* 0x58 degrees */
};

class CBall : public CObject {
public:
    typedef bool (CBall::*StateFunc)();

    CBall(Vec* from, Vec* to, float spin, int kind);
    virtual ~CBall();                        /* fn_1_1428 */
    u8 isLanded();                           /* fn_1_1498 u8 (as IsShot) */
    Vec* getPos();                           /* fn_1_14A4 */
    Vec* predict(Vec* out, float sec);       /* fn_1_14AC position `sec` seconds ahead on the arc */
    void hold(Vec* pos);                     /* fn_1_157C follows the hand (player holdBall) */
    void throwTo(Vec* to);                   /* fn_1_15D8 54-frame ballistic arc */
    virtual void update();                   /* fn_1_1788 deletes itself when the state returns false */
    bool stateIdle();                        /* fn_1_1834 */
    bool stateFly();                         /* fn_1_183C */
    void Land();                             /* fn_1_18A4 */
    bool stateLandWait();                    /* fn_1_191C false at the motion end */
    bool stateThrown();                      /* fn_1_197C */
    bool CheckArrive();                      /* fn_1_1A28 only while descending (retail H6) */

    /* PTMF stores go through a by-value copy (three words to a stack temp) */
    void setState(StateFunc state) { m_state = state; }

    StateFunc m_state;                       /* 0x14 (12 bytes on CW) */
    CModel m_model;                          /* 0x20 link copy of master kind & 3 */
    bool m_landed;                           /* 0x22 */
    Vec m_pos;                               /* 0x24 */
    Vec m_target;                            /* 0x30 */
    Vec m_vel;                               /* 0x3C */
    Vec m_accel;                             /* 0x48 fly acceleration: normalize(to - from) * g */
    float* m_spinPtr;                        /* 0x54 "star_a" rot.y */
    float m_spin;                            /* 0x58 */
    float m_dist;                            /* 0x5C distance to the target */
};

} // namespace m532

#ifndef __MWERKS__
template <> m532::CBallMan* CSingleton<m532::CBallMan>::ms_pointer; /* defined in ball.cpp (bss_C) */
#endif

#endif
