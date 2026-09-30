#ifndef M513_KURIBO_H
#define M513_KURIBO_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m513Dll/a_set.h"
#include <vector>

namespace m513 {

class CKuribo : public TLinkItem<CKuribo> {
public:
    typedef void (CKuribo::*ProcFunc)();
    enum { NUMBEROF_MOTION = 4 };
    /* motion slots: 0 0x470010 idle, 1 0x470011 end, 2 0x470012 walk / turn, 3 0x470013 excited */

    CKuribo(Vec* pos, Vec* rot);   /* fn_1_EDE0 */
    ~CKuribo();                    /* fn_1_F1E4 */
    void addMotion(int dataNum);   /* fn_1_F2AC */
    void setMotion(int no, bool once, float shift); /* fn_1_F334 */
    void procTurn();               /* fn_1_F3EC PTMF data_5EC */
    void procReact();              /* fn_1_F698 PTMF data_5E0 / 63C */
    void procEnd();                /* fn_1_F9F0 PTMF data_648 */
    void startEnd();               /* fn_1_FAE4 (gamemaster showRecord) */
    void update();                 /* fn_1_FBA8 PTMF gamemaster data_40C */
    void setMode(int mode);        /* fn_1_FC08 (gamemaster updateKuribo) */
    void setProc(ProcFunc proc) { m_proc = proc; }

    /* 0x00 CLinkNode (TLinkItem), on ASet<CKuribo> */
    CModel m_model;             /* 0x08 0x47000F */
    Vec m_pos;                  /* 0x0C */
    float m_unk18;              /* 0x18 60.000004, never read */
    Vec m_rot;                  /* 0x1C */
    int m_motion;               /* 0x28 -1 = none */
    int m_reactMotion;
    std::vector<s16> m_mot_id;  /* 0x30 */
    int m_state;                /* 0x3C */
    float m_time;               /* 0x40 */
    int m_dir;                  /* 0x44 rot.y == 135 ? 0 : 1 (exact compare, retail) */
    float m_wait;               /* 0x48 */
    int m_mode;                 /* 0x4C -1 */
    ProcFunc m_proc;            /* 0x50 (12 bytes on CW) */
};

} // namespace m513

#ifndef __MWERKS__
template <> ASet<m513::CKuribo>* ASet<m513::CKuribo>::sm_ptr; /* defined in gamemaster.cpp */
#endif

#endif
