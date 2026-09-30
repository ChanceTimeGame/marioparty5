#ifndef M513_PLAYER_H
#define M513_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m513Dll/a_set.h"
#include "REL/m513Dll/input.h"
#include "REL/m513Dll/leaf.h"
#include "REL/m513Dll/powereff.h"
#include <memory>
#include <vector>

namespace m513 {

class CPlayer : public TLinkItem<CPlayer> {
public:
    typedef void (CPlayer::*ProcFunc)();
    enum { NUMBEROF_MOTION = 6, EFF_NUM = 16 };
    /* motion slots: 0 0x8C0000 idle, 1 0x8C0001 result turn, 2 0x8C0002 (never selected), 3 0x8C0074 pump,
     * 4 0x8C0006 win, 5 0x8C0007 lose */

    /* by value: a PTMF store goes through a stack temporary */
    void setProc(ProcFunc proc) { m_proc = proc; }
    void Stop() { setProc(&CPlayer::procStop); }
    void Start() { setProc(&CPlayer::procStart); }

    static CInput* CreateInput(int idx);     /* fn_1_11844 (unreferenced; inlined in the ctor) */
    CPlayer(int idx, bool deca);             /* fn_1_11900 */
    void addMotion(int dataNum);             /* fn_1_12008 */
    void update();                           /* fn_1_12080 PTMF gamemaster data_3E8 */
    void setMotion(int no, bool force, bool once, float shift); /* fn_1_1212C */
    void procIdle();                         /* fn_1_12204 PTMF data_7F8 (the ctor's) */
    void procStop();                         /* fn_1_12208 PTMF pair (gamemaster data_3C4) */
    void procStart();                        /* fn_1_1220C PTMF pair (gamemaster data_3B8) */
    void procControl();                      /* fn_1_122F8 PTMF data_848 */
    void procFinished();                     /* fn_1_128AC PTMF data_854 */
    void procTimeout();                      /* fn_1_12B20 PTMF data_894 (same body as procFinished) */
    void procFaceCamera();                   /* fn_1_12D94 PTMF data_87C / 888 */
    int getMotion() const;                   /* fn_1_12E88 (gamemaster updateKuribo) */
    void SetResult(bool win);                /* fn_1_12E90 (gamemaster setResult) AddWinner on a win */
    void timeUp();                           /* fn_1_12FDC (gamemaster checkRecord) */
    bool IsCom() const;                      /* fn_1_13050 (gamemaster checkRecord) */
    void cheerHeiho();                       /* fn_1_13080 */

    /* read by gamemaster (const accessors) */
    int IsTurning() const { return m_turning; }
    bool IsFinished() const { return m_finished; }
    u32 GetTime() const { return m_time; }
    int GetIdx() const { return m_idx; }
    int GetCharNo() const { return m_charNo; }

    /* 0x00 CLinkNode (TLinkItem), on ASet<CPlayer> */
    Vec m_pos;                                       /* 0x08 x = 200 idx - 300, z 250 */
    float m_unk14;                                   /* 0x14 60.000004, never read */
    Vec m_rot;                                       /* 0x18 {0, 180, 0}, then eased toward the camera */
    int m_turning;                                   /* 0x24 1; 0 once facing the camera (gamemaster tests > 0) */
    ProcFunc m_proc;                                 /* 0x28 (12 bytes on CW) */
    int m_charNo;                                    /* 0x34 GwPlayerConf[idx].charNo */
    int m_motion;                                    /* 0x38 -1 = none */
    int m_idx;                                       /* 0x3C */
    int m_resultState;                               /* 0x40 */
    float m_resultTime;                              /* 0x44 */
    u32 m_time;                                      /* 0x48 finish time (CScore::getValue; gamemaster: cmplw) */
    float m_pumpTime;                                /* 0x4C */
    bool m_finished;                                 /* 0x50 */
    bool m_deca;                                     /* 0x51 gamemaster m_deca: GwPlayer.mgScore = time */
    std::auto_ptr<CPowerEff> m_eff[EFF_NUM];         /* 0x54 __construct_array */
    int m_effIdx;                                    /* 0x94 ring index */
    std::vector<s16> m_mot_id;                       /* 0x98 */
    std::auto_ptr<CModel> m_model;                   /* 0xA4 CModel(charNo, 3) */
    std::auto_ptr<CInput> m_input;                   /* 0xA8 CreateInput(idx) (polymorphic delete) */
    std::auto_ptr<CLeaf> m_leaf;                     /* 0xAC */
};

} // namespace m513

#ifndef __MWERKS__
template <> ASet<m513::CPlayer>* ASet<m513::CPlayer>::sm_ptr; /* defined in gamemaster.cpp */
#endif

#endif
