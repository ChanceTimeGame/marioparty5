/* player.h -- m568::CPlayer (player.cpp): one of the four riders. It owns its input (pad or COM), its character
 * model and its tube; per frame (PTMF from game_master) it feeds the input to the tube and poses the model on it.
 * The result PTMFs (game_master thread_exec) set m_isWinner, AddWinner the winners and delete the losers' tubes.
 * No virtuals, no vptr: CLinkNode at offset 0 on every ABI. Owned by ASet<CPlayer> (game_master.o bss A0C); the
 * dtor is the implicit inline one (~CObjSet inlines it). player.h does not include minigame.h (player.cpp does).
 * NOTE (skeleton, vs DESIGN "Sides"): +0x28 = (GwPlayerConf.grp == 0) (10760) equals the tube's m_isSolo (the
 * tube stores (arg == 0) of the player's `grp == 0 ? 0 : 1`, 12094), so it is named m_isSolo here; FDEC (all team
 * tubes out) then sets m_isWinner = m_isSolo: the solo wins. Names are ours (W0 proposals).
 * GC: TLinkItem<CPlayer> +0, m_input +0x08, m_proc +0x0C (12-byte PTMF), m_idx +0x18, m_charNo +0x1C, m_curMot
 * +0x20, m_spin +0x24, m_isSolo +0x28, m_sphere +0x2C, m_unk3C +0x3C, m_isWinner +0x40, m_mot_id +0x44,
 * m_model +0x50, m_tube +0x54; size 0x58 (game_master `li r3,0x58`). */
#ifndef M568_PLAYER_H
#define M568_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/om.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m568Dll/a_set.h"
#include "REL/m568Dll/input.h"
#include "REL/m568Dll/tube.h"
#include <memory>
#include <vector>

namespace m568 {

/* fn_1_FD14 (unreferenced; inlined into CreateTube / the ctor): GwPlayerConf[idx].grp == 0 */
bool IsSolo(int idx);

/* setStartPos's overlap counter (name ours): FD38 is its operator() (unreferenced; inlined into ForEachPair) */
struct HitCounter {
    void operator()(CSphere* a, CSphere* b); /* fn_1_FD38 ++n when they overlap */
    int count() const { return n; }          /* inline (setStartPos) */
    int n;
};

class CPlayer : public TLinkItem<CPlayer> {
public:
    typedef void (CPlayer::*ProcFunc)();
    enum { NUMBEROF_MOTION = 8 };
    /* motion slots: 0 idle ride, 1 B (paddle), 2 A, 3 steer pose (paused, frame from the stick), 4 knocked out,
     * 5 result idle, 6 win, 7 lose */

    void resetPos();                        /* fn_1_FD8C (unreferenced) */
    void startResultSoloWin();              /* fn_1_FDEC PTMF data_2E4 (every team tube out) */
    void startResultTeamWin();              /* fn_1_FE8C PTMF data_2F0 */
    void startWinLoseMotion();              /* fn_1_FF34 PTMF data_2FC */
    void startWinLoseMotion2();             /* fn_1_FF8C PTMF data_308 (same body) */
    void finish();                          /* fn_1_FFE4 AddWinner; drops the input; losers drop the tube */
    void procResult();                      /* fn_1_100F8 PTMF data_5A8 / 5B4 */
    /* fn_1_1019C: z by side; the team's x is the first slot of {-300, 0, 300, 600} whose sphere overlaps no
     * other player (else assert(!"DIE!") player.cpp:140) */
    void setStartPos(float zTeam, float zSolo);
    static CTube* CreateTube(int idx);      /* fn_1_10320 (unreferenced; inlined into the ctor) */
    static CInput* CreateInput(int idx);    /* fn_1_103D4 (unreferenced; inlined into the ctor) */
    CPlayer(int idx);                       /* fn_1_104FC */
    void addMotion(int dataNum);            /* fn_1_10E14 */
    void update();                          /* fn_1_10E9C PTMF data_2CC */
    void setMotion(int no, bool once);      /* fn_1_10F54 */
    void procInit();                        /* fn_1_11098 PTMF data_5EC */
    void procMain();                        /* fn_1_11230 PTMF data_61C */
    void control();                         /* fn_1_11268 */
    void updateModel();                     /* fn_1_11380 */
    void steer(float x);                    /* fn_1_11630 team only */
    void motionB();                         /* fn_1_11784 team only */
    void motionA();                         /* fn_1_1184C team only */

    /* ForEachSpherePair's accessor (inline: retail copies the result into the functor's parameter) */
    CSphere* GetSphere() { return &m_sphere; }

    /* inline (updateModel): the model's matrix = m translated to pos */
    inline void setModelPos(Mtx m, const Vec* pos);

    /* PTMF stores go through a by-value copy (a stack temporary) */
    void setProc(ProcFunc proc) { m_proc = proc; }

    /* 0x00 CLinkNode (through TLinkItem), on ASet<CPlayer> */
    std::auto_ptr<CInput> m_input;   /* 0x08 CreateInput(idx) (polymorphic delete) */
    ProcFunc m_proc;                 /* 0x0C (12 bytes on CW) */
    int m_idx;                       /* 0x18 */
    int m_charNo;                    /* 0x1C GwPlayerConf[idx].charNo (used as s16) */
    int m_curMot;                    /* 0x20 -1 = none */
    float m_spin;                    /* 0x24 degrees (knocked-out tumble) */
    bool m_isSolo;                   /* 0x28 GwPlayerConf[idx].grp == 0 */
    CSphere m_sphere;                /* 0x2C start-slot test sphere (r 150) */
    int m_unk3C;                     /* 0x3C = 0, never read */
    bool m_isWinner;                 /* 0x40 */
    std::vector<int> m_mot_id;       /* 0x44 eight motion ids (4-byte elements: keep int) */
    std::auto_ptr<CModel> m_model;   /* 0x50 CModel(charNo, 2) */
    std::auto_ptr<CTube> m_tube;     /* 0x54 CreateTube(idx) (the losers' reset(0) in finish) */
};

} // namespace m568

#ifndef __MWERKS__
template <> ASet<m568::CPlayer>* ASet<m568::CPlayer>::sm_ptr; /* defined in game_master.cpp */
#endif

#endif
