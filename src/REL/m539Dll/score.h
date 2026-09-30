#ifndef M539_SCORE_H
#define M539_SCORE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m539Dll/a_set.h"
#include "REL/m539Dll/man_map.h"
#include "REL/m539Dll/scorespr.h"
#include <memory>

namespace m539 {

class CDrum;

class CScore : public TLinkItem<CScore> {
public:
    typedef void (CScore::*Func)();

    /* fn_1_FAB4 (unreferenced): the first call loads dataNum into *cache, later calls link a copy */
    static CModel* LoadModelCached(u32 dataNum, CModel** cache);
    /* fn_1_FB54 (unreferenced; inlined into the ctor): a digit wheel at the board's "sd%02d" object */
    static CModel* CreateDigit(CModel* board, int n);
    void setDigit(int i, float v);  /* fn_1_FC08 (unreferenced; inlined into the ctor and update) */
    CScore(int no);                 /* fn_1_FCF0 */
    static void UpdateCell(CDrum* d); /* fn_1_10388 d->Update() (unreferenced; inlined into update) */
    static void StartCell(CDrum* d);  /* fn_1_103B0 d->Start()  (inlined into startSpin) */
    static void PressCell(CDrum* d);  /* fn_1_103D8 d->Press()  (inlined into finishB) */
    void start();                   /* fn_1_10400 CPlayer::proc_enterJump: head motion + SE 0x7E4 */
    void finishA();                 /* fn_1_1044C PTMF (thread_exec step 9): block scale to 0, SE, board 0 bursts */
    void appear();                  /* fn_1_104A8 CPlayer::proc_ready: block scale to 1 (board 0: SE + burst) */
    void spawnBlockEffect();
    void update();                  /* fn_1_105F4 PTMF (every frame, CGameMaster::on_update) */
    void startSpin();               /* fn_1_10A90 CPlayer::proc_enterLand: all reels spin, spin SE */
    void finishB();                 /* fn_1_10B58 PTMF (thread_exec step 10): every reel's Press */
    void stopNext();                /* fn_1_10BE8 CPlayer::stateJump (the apex): stop the next ring reel */
    int checkLine(int line);        /* fn_1_10CEC CGameMaster::thread_exec tally: the line's payout */
    static bool IsAllStopped();     /* fn_1_10E64 every board has stopped its 8 reels */
    void updateBlockMtx();          /* fn_1_10F14 the block's -15 deg Y tilt and m_scale */

    /* f(cell) for every reel that exists (inline; UpdateCell/StartCell/PressCell are its retail callbacks,
     * inlined through the constant pointer: the extra get()/parameter register hops of update/startSpin/finishB) */
    void execCells(void (*f)(CDrum*))
    {
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                CDrum* d = m_cell[r][c].get();
                if (d) {
                    f(d);
                }
            }
        }
    }

    /* 0x00 CLinkNode (through TLinkItem), on ASet<CScore> */
    int m_no;                           /* 0x08 player 0..3 */
    u8 m_unk0C[0x10];                   /* 0x0C never touched in any unit */
    std::auto_ptr<CModel> m_base;       /* 0x1C 0x610002, LOOP, camera 1 << no */
    std::auto_ptr<CModel> m_board;      /* 0x20 0x610003: the "d<r><c>" / "sd%02d" objects */
    std::auto_ptr<CDrum> m_cell[3][3];  /* 0x24 the reels ([1][1] has no body: the wild) */
    std::auto_ptr<CModel> m_block;      /* 0x48 0x610009 the "block" object (pulses when a line pays) */
    std::auto_ptr<CModel> m_head;       /* 0x4C 0x610004 the "head" object (the player lands on it) */
    std::auto_ptr<CModel> m_digit[3];   /* 0x50 0x610008 each: ones, tens, hundreds */
    Vec m_headPos;                      /* 0x5C "head" translation (CPlayer reads it) */
    Vec m_headPrev;
    Vec m_headVel;                      /* 0x74 m_headPos - m_headPrev (CPlayer reads .y) */
    float m_angle;                      /* 0x80 pi in the ctor, 0 at each stop; never read */
    CLerp<float> m_scale;               /* 0x84 block scale */
    CLerp<float> m_disp;                /* 0x98 displayed score */
    int m_stopCount;                    /* 0xAC 0..8 */
    int m_score;                        /* 0xB0 sum of line payouts (CGameMaster::setResult) */
    std::auto_ptr<CScoreSpr> m_spr;     /* 0xB4 never set by any unit (retail dead) */
    int m_unkB8;                        /* 0xB8 0, never used */
    int m_spinSe;
    int m_lastDisp;                     /* 0xC0 */
    int m_tick;                         /* 0xC4 3-frame SE latch */
};

} // namespace m539

#ifndef __MWERKS__
template <> ASet<m539::CScore>* ASet<m539::CScore>::sm_ptr; /* defined in game_master.cpp */
#endif

#endif
