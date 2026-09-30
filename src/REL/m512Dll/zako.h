/* zako.h -- the crowd of eight runners on the track (zako.cpp; scenery: nothing else reads them):
 * m512::CZakoMan (the hidden master model holding the joint motions, owns the pool) and m512::CZako (one
 * runner, a PTMF state machine start -> walk -> dash -> brake -> walk). zako.cpp includes minigame.h (the
 * 120/210/210 triple is in zako.o). Class names are ours (W0 proposals). */
#ifndef M512_ZAKO_H
#define M512_ZAKO_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include <vector>

namespace m512 {

/* GC: CGameObject +0x00 (vptr +8), empty CSingleton<CZakoMan> at +0x10, m_mot_id +0x10, m_model +0x1C;
 * size 0x20 (gamemaster `li r3,0x20`). Vtable data_580 {~, on_new_mode, on_update}. */
class CZakoMan : public CGameObject, public CSingleton<CZakoMan> {
public:
    enum { NUMBEROF_PMOTION = 3 };

    CZakoMan();
    s16 createMotion(int dataNum);  /* fn_1_E904 Hu3DJointMotion on m_model; push_back; returns the id */
    virtual ~CZakoMan();
    virtual void on_update();
    virtual void on_new_mode(int mode);

    std::vector<s16> m_mot_id; /* 0x10 walk, dash, brake (joint motions of m_model) */
    CModel m_model;            /* 0x1C 0x460009, DISPOFF: the hidden master */
};

/* A plain list item (no vptr). GC: TLinkItem (CLinkNode) +0x0 ... m_model +0x5C; size 0x60 (zako `li r3,0x60`). */
class CZako : public TLinkItem<CZako> {
public:
    typedef void (CZako::*StateFunc)();

    static float SubAngle(float a, float b);               /* fn_1_EB1C unreferenced (= m536 9B50) */
    static float SubAngleMax(float a, float b, float max); /* fn_1_EBD4 unreferenced (= m536 9C08) */
    CZako(Vec* pos);                                       /* fn_1_ED38 */
    static void DeleteAll();   /* fn_1_EF9C CZakoMan dtor */
    static void UpdateAll();   /* fn_1_F070 Update each, then rotate the list by one */
    static void Update(CZako* z);  /* fn_1_F0F4 */
    void updateModel();        /* fn_1_F168 rot (0, yaw, 0), pos */
    void CheckPush();          /* fn_1_F1E4 push apart from every other zako closer than 120 */
    void setMotion(int motion, bool once); /* fn_1_F3F0 unreferenced copy (inlined into the states) */
    void stateStart();         /* fn_1_F4F0 */
    void stateWalk();          /* fn_1_F534 */
    void stateDash();          /* fn_1_F7CC */
    void stateBrake();         /* fn_1_F968 */
    bool move();               /* fn_1_FB38 pos += step along the yaw; result never used */
    bool ClampTrack();         /* fn_1_FCCC keep on the track and off the referee stand; true = stand/outer wall */
    float GetTrackAngle();     /* fn_1_10444 track tangent, degrees */
    /* by value: retail copies each PTMF constant to a stack temporary before storing it */
    void setState(StateFunc state) { m_state = state; }

    static TLinkList<CZako> list; /* bss AA0; its DestructorChain A94 */

    u8 m_unk08;          /* 0x08 never accessed */
    bool m_hit;          /* 0x09 wall/stand contact this frame; never tested */
    StateFunc m_state;   /* 0x0C (12 bytes on CW; called with no __ptmf_test) */
    int m_motion;        /* 0x18 current m_mot_id index, -1 */
    float m_yaw;         /* 0x1C degrees */
    float m_steer;       /* 0x20 offset from the tangent, eased 2 degrees/frame toward m_steerTarget */
    float m_steerTarget; /* 0x24 */
    float m_speed;       /* 0x28 */
    int m_pushTimer;     /* 0x2C never read (retail) */
    int m_unk30;         /* 0x30 ctor 0 (mem-initializer), never read */
    Vec m_pos;           /* 0x34 */
    Vec m_unk40;         /* 0x40 ctor 0, never read */
    float m_unk4C;       /* 0x4C ctor 0, never read */
    int m_dashTimer;     /* 0x50 */
    int m_unk54;         /* 0x54 ctor 0, never read */
    float m_radius;      /* 0x58 written by ClampTrack, never read */
    CModel m_model;      /* 0x5C own model 0x460009 */
};

} // namespace m512

#ifndef __MWERKS__
template <> m512::CZakoMan* CSingleton<m512::CZakoMan>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
