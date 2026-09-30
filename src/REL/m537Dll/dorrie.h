/* dorrie.h -- m537::CDorrie (dorrie.cpp): one player's Dorrie (model 0x5F0003 + player, motions 0x5F0009 /
 * 0x5F0008) with its rider object (0x5F0007, m_sub). It turns to a yaw set by SetAngle over a cosine ease
 * (UpdateTurn), plays its motion once the turn is done when RequestMotion was called (UpdateMotion), and pushes a
 * ripple into the water every 300 frames (UpdateRipple). Players drive it through update / RequestMotion /
 * SetAngle / GetObjMtx only (sheet §7).
 * m537::CAngleD: a double scalar wrapped into [min, max) -- the double version of m532's CAngle (player.h has the
 * float one; two classes of one name cannot share the namespace). Defined at the end of dorrie.cpp in retail order
 * set, ==, !=, lerp, wrap, get, ctor, [insert<s16>], diff(a, b).
 * GC (sheet §7.1; size 0x68, stage `li r3,0x68`; NO vtable, non-virtual dtor called directly by auto_ptr / reset):
 * CModel base +0 (2 + 6 pad: the class is 8-aligned), m_angle +0x08 (0x20), m_angleFrom +0x28, m_angleTo +0x30,
 * m_turnTime +0x38, m_turnDuration +0x40 (doubles), m_motionReq +0x48, m_frame +0x4C, m_motion_id +0x50
 * (vector<s16>: +0x54 size, +0x58 data), m_shadowDelay +0x5C, m_sub +0x60, 4 pad.
 * The CModel base and the doubles: on the host the offsets differ (nothing outside dorrie.cpp reads a member). */
#ifndef M537_DORRIE_H
#define M537_DORRIE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include <memory>
#include <vector>

namespace m537 {

class CAngleD {
public:
    void set(double v);                      /* fn_1_6A58 m_value = wrap(v) */
    bool operator==(double v);               /* fn_1_6A94 m_value == wrap(v) */
    bool operator!=(double v);               /* fn_1_6ADC */
    void lerp(double a, double b, double t); /* fn_1_6B28 m_value = wrap(a + diff(a, b) * t) */
    double wrap(double v);                   /* fn_1_6B8C */
    double get();                            /* fn_1_6C18 */
    CAngleD(double a, double b, double v);   /* fn_1_6C20 (wrap inlined) */
    double diff(double a, double b);         /* fn_1_70BC the shortest signed difference b - a */

    double m_min;   /* 0x00 */
    double m_max;   /* 0x08 */
    double m_range; /* 0x10 */
    double m_value; /* 0x18 */
};

class CDorrie : public CModel {
public:
    enum { NUMBER_OF_MOTION = 2 };
    enum { OBJ_STAGE = 0, OBJ_SPLING = 1 };

    CDorrie(int no);                        /* fn_1_5E4C */
    ~CDorrie();                             /* fn_1_61AC NON-virtual */
    void update();                          /* fn_1_6278 (player Update) */
    void UpdateTurn();                      /* fn_1_6308 */
    void UpdateRipple();                    /* fn_1_648C CWater::AddForce every 300 frames */
    Mtx* GetObjMtx(int which, Mtx m);       /* fn_1_6558 (camera SetWinnerView, player updatePos) */
    Vec* GetObjPos(int which, Vec* out);    /* fn_1_65FC */
    void SetAngle(double to, double time);  /* fn_1_66D0 (stage CreateDorrie, player Reposition) */
    void RequestMotion();                   /* fn_1_672C (player CheckFall) */
    void UpdateMotion();                    /* fn_1_6738 */
    void LoadMotion();                      /* fn_1_6808 assert dorrie.cpp:179 */
    void AddMotion(u32 data);               /* fn_1_68C0 */
    void PlayMotion(int idx, bool loop);    /* fn_1_694C */

    /* 0x00 CModel base (0x5F0003 + no) */
    CAngleD m_angle;               /* 0x08 CAngleD(0.0, 360.0, 0.0) */
    double m_angleFrom;            /* 0x28 */
    double m_angleTo;              /* 0x30 */
    double m_turnTime;             /* 0x38 seconds, += 1/60 */
    double m_turnDuration;         /* 0x40 seconds */
    bool m_motionReq;              /* 0x48 */
    int m_frame;                   /* 0x4C ++ per update, % 300 */
    std::vector<s16> m_motion_id;  /* 0x50 (retail name: the assert text) */
    int m_shadowDelay;             /* 0x5C 170: setShadowMap() when it reaches 0 */
    std::auto_ptr<CModel> m_sub;   /* 0x60 0x5F0007 */
};

} // namespace m537

#endif
