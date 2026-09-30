#ifndef M517_PLAYER_H
#define M517_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/om.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m517Dll/a_set.h"
#include "REL/m517Dll/input.h"
#include "REL/m517Dll/effect.h"
#include "REL/m517Dll/papereff.h"
#include "REL/m517Dll/dusteff.h"
#include "REL/m517Dll/choro.h"
#include <memory>
#include <vector>

namespace m517 {

class CChoro;

/* the four ride-in carriers ("1p" / "3p" / "4p" / "2p" hooks), dropped after the start message */
class CPlayerCarrier : public CSingleton<CPlayerCarrier> {
public:
    enum { NUM = 4 };

    CPlayerCarrier();  /* fn_1_15500 (gamemaster thread_exec) */
    ~CPlayerCarrier(); /* fn_1_15724 */
    /* fn_1_157D0 (unreferenced; inlined in CPlayer::procIntro): hook i's pos / rot (rot.y + 90); returns whether the
     * carrier motion is still running (the inlined caller drops it) */
    bool getHookPos(int i, Vec* pos, Vec* rot);

    std::auto_ptr<CModel> m_model[NUM]; /* 0x00 s_model[i] */
};

/* fn_1_158A8 (unreferenced; the functor of the start-position search): counts the sphere pairs that overlap */
struct HitCounter {
    void operator()(CSphere* a, CSphere* b);
    int count() const { return m_count; }

    int m_count; /* the functor itself is the counter (fn_1_158A8 increments this+0) */
};

/* fn_1_177CC (unreferenced; inlined): from + rate * the shortest (-180, 180] difference, wrapped to [0, 360) */
float AngleLerp(float from, float to, float rate);
/* fn_1_195A8 (unreferenced): atan2(v.x, v.z) in degrees */
float VecYaw(const Vec* v);

class CPlayer : public TLinkItem<CPlayer> {
public:
    typedef void (CPlayer::*ProcFunc)();
    enum { NUMBEROF_MOTION = 14 };
    /* motion slots: 0 0x8C0000 idle, 1 walk, 2 run, 3 0x8C0003 pop out, 4 0x8C0004 land, 5 0x8C003A stun,
     * 6 0x8C0013 jump / hit, 7 0x8C0014 intro land, 8 0x8C0051 gallery idle, 9 0x87002D ride idle, 10 0x870097
     * ride, 11 0x870098 ride slow, 12 0x8C0030 win, 13 lose (team 0x8C0031, solo 0x8C002E) */

    /* by value: a PTMF store goes through a stack temporary */
    void setProc(ProcFunc proc) { m_proc = proc; }
    void Intro() { setProc(&CPlayer::procIntro); }
    void Start() { setProc(&CPlayer::procStart); }

    void SetStartPosDefault();                  /* fn_1_158FC (unreferenced) SetStartPos(250, -300) */
    void Finish();                              /* fn_1_1593C (gamemaster FinishAll) */
    void SetStartPos(float teamZ, float soloZ); /* fn_1_15A78 (inlined in the ctor) */
    static CBall* CreateRide(int idx);          /* fn_1_15BF0 (unreferenced; inlined in the ctor) */
    static CInput* CreateInput(int idx);        /* fn_1_15C6C (unreferenced; inlined in the ctor) */
    CPlayer(int idx);                           /* fn_1_15DC8 assert player.cpp:227 */
    void addMotion(int dataNum);                /* fn_1_168A0 */
    void update();                              /* fn_1_16918 PTMF gamemaster data_374 */
    void setMotion(int no, bool once, float shift); /* fn_1_16A7C (inlined 30+ times; this copy: the ctor) */
    void procNone();                            /* fn_1_16B64 PTMF data_76C (the ctor's) */
    void procIntro();                           /* fn_1_16B68 PTMF header triple */
    void procStart();                           /* fn_1_17614 PTMF header triple */
    void procPlay();                            /* fn_1_178D0 */
    void procOut();                             /* fn_1_179B0 */
    void procStay();                            /* fn_1_17FC0 m_immune = 0 */
    void Hit(CBall* ball);                      /* fn_1_17FCC (effect CBall::HitPlayer) */
    void Stun(CChoro* choro);                   /* fn_1_183C4 (choro CChoro::HitPlayer) */
    void SetResult(bool win);                   /* fn_1_184E8 (gamemaster setResult) */
    Vec GetOutPos() const;                      /* fn_1_186F0 (hidden result) */
    void procReturnSolo();                      /* fn_1_1877C */
    void procReturnTeam();                      /* fn_1_18EDC */
    void procReturn();                          /* fn_1_19560 */
    void MoveSolo(Vec stick);                   /* fn_1_19600 */
    void Fall();                                /* fn_1_19AB8 */
    void MoveTeam(Vec stick);                   /* fn_1_19B60 */
    void ClampArena();                          /* fn_1_1A0B4 */
    static void PushPair(CPlayer* a, CPlayer* b); /* fn_1_1A230 gamemaster ForEachPair<CPlayer> */

    /* read across units (gamemaster, effect, choro, input) */
    bool IsSolo() const { return m_isSolo; }
    bool IsOut() const { return m_out; }
    int GetIdx() const { return m_idx; }
    Vec* GetPos() { return &m_sphere.pos; }
    CSphere* GetSphere() { return &m_sphere; }

    /* 0x00 CLinkNode (TLinkItem), on ASet<CPlayer> */
    int m_immune;                     /* 0x08 1 while returning home (gamemaster IsAllIdle: > 0) */
    bool m_out;                       /* 0x0C caught (the solo wins when all three are) */
    ProcFunc m_proc;                  /* 0x10 (12 bytes on CW) */
    int m_idx;                        /* 0x1C player number */
    int m_teamIdx;                    /* 0x20 solo 0, team 1..3 */
    int m_charNo;                     /* 0x24 GwPlayerConf[idx].charNo */
    int m_motion;                     /* 0x28 index, -1 = none (input reads == 5: stunned) */
    bool m_isSolo;                    /* 0x2C GwPlayerConf[idx].grp == 0 */
    CSphere m_sphere;                 /* 0x30 pos, r = 60.000004 */
    Vec m_rot;                        /* 0x40 */
    Vec m_scale;                      /* 0x4C {1, 1, 1}; y squashed in procOut */
    Vec m_vel;                        /* 0x58 */
    Vec m_move;                       /* 0x64 pos - prev (input CInputComSolo) */
    Vec m_outPos;                     /* 0x70 the gallery spot (GetOutPos) */
    int m_outState;                   /* 0x7C procOut */
    int m_introState;                 /* 0x80 procIntro */
    float m_introTime;                /* 0x84 */
    Vec m_home;                       /* 0x88 procReturn's goal */
    Vec m_jumpTo;
    bool m_introDust;                 /* 0xA0 */
    float m_outTime;
    int m_stun;                       /* 0xA8 frames since the stun (45 = free) */
    bool m_finished;                  /* 0xAC */
    int m_homeState;                  /* 0xB0 */
    std::vector<s16> m_mot_id;        /* 0xB4 */
    std::auto_ptr<CModel> m_model;    /* 0xC0 CModel(charNo, 2) */
    std::auto_ptr<CInput> m_input;    /* 0xC4 CreateInput(idx) (virtual delete) */
    std::auto_ptr<CBall> m_ball;      /* 0xC8 the solo's ride (CreateRide) */
    std::auto_ptr<CPaper> m_paper;
    std::auto_ptr<CShadow2> m_shadow; /* 0xD0 the solo's blob shadow */
};

} // namespace m517

#ifndef __MWERKS__
template <> ASet<m517::CPlayer>* ASet<m517::CPlayer>::sm_ptr;                     /* defined in input.cpp (A08) */
template <> m517::CPlayerCarrier* CSingleton<m517::CPlayerCarrier>::ms_pointer;   /* defined in effect.cpp (.bss 4) */
#endif

#endif
