#ifndef M513_HEIHO_H
#define M513_HEIHO_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m513Dll/a_set.h"
#include <memory>
#include <vector>

namespace m513 {

class CHeihoCarrier : public CSingleton<CHeihoCarrier> {
public:
    CHeihoCarrier();  /* fn_1_D738 */
    ~CHeihoCarrier(); /* fn_1_D88C */
    /* fn_1_D934 (unreferenced; inlined in CHeiho::procMain): the hook object's pos / rot (rot.y + 90);
     * returns whether the carrier's motion is still running */
    bool getHookPos(int i, Vec* pos, Vec* rot);

    std::auto_ptr<CModel> m_model; /* 0x00 0x47000D */
};

class CHeiho : public TLinkItem<CHeiho> {
public:
    typedef void (CHeiho::*ProcFunc)();
    enum { NUMBEROF_MOTION = 4 };
    /* motion slots: 0 0x470009 idle, 1 0x47000B hop, 2 0x47000C throw, 3 0x47000A cheer */

    CHeiho(int idx);                 /* fn_1_DA0C */
    ~CHeiho();                       /* fn_1_DE94 (does not kill m_item: retail) */
    void createItem();               /* fn_1_DF5C */
    void releaseItem();              /* fn_1_E030 (unreferenced; inlined in procMain) */
    void giveLeaf();                 /* fn_1_E084 (unreferenced; inlined in procMain) */
    void procNone();                 /* fn_1_E138 PTMF data_53C / 548 */
    void procMain();                 /* fn_1_E13C PTMF data_4D4 */
    void update();                   /* fn_1_E5F0 PTMF gamemaster data_400 */
    void addMotion(int dataNum);     /* fn_1_E650 */
    void setMotion(int no, bool once, float shift); /* fn_1_E6D8 */
    void cheer();                    /* fn_1_E790 (player) */

    int GetIdx() const { return m_idx; }
    void setProc(ProcFunc proc) { m_proc = proc; }

    /* 0x00 CLinkNode (TLinkItem), on ASet<CHeiho> */
    CModel m_model;             /* 0x08 0x470008 */
    int m_motion;               /* 0x0C -1 = none */
    std::vector<s16> m_mot_id;  /* 0x10 */
    Vec m_pos;                  /* 0x1C */
    float m_unk28;              /* 0x28 60.000004, never read */
    Vec m_rot;                  /* 0x2C */
    int m_idx;                  /* 0x38 player number */
    int m_state;                /* 0x3C */
    float m_time;               /* 0x40 */
    HU3DMODELID m_item;         /* 0x44 the thrown item model */
    float m_seTime;             /* 0x48 */
    int m_throwFrame;           /* 0x4C 255 = thrown */
    ProcFunc m_proc;            /* 0x50 (12 bytes on CW) */
};

} // namespace m513

#ifndef __MWERKS__
template <> m513::CHeihoCarrier* CSingleton<m513::CHeihoCarrier>::ms_pointer; /* defined in leaf.cpp */
template <> ASet<m513::CHeiho>* ASet<m513::CHeiho>::sm_ptr;                   /* defined in gamemaster.cpp */
#endif

#endif
