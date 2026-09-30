#ifndef M512_HEIHO_H
#define M512_HEIHO_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include <vector>

namespace m512 {

class CHeihoMan : public CGameObject, public CSingleton<CHeihoMan> {
public:
    typedef void (CHeihoMan::*ProcFunc)();
    enum { NUMBEROF_MOTION = 2 };

    CHeihoMan();
    s16 createMotion(int dataNum);  /* fn_1_109F0 Hu3DJointMotion on m_model; push_back; returns the id */
    virtual void on_update();       /* fn_1_10A88 if (m_proc) (this->*m_proc)() */
    void proc_start();              /* fn_1_10AD0 start motion; SE 0x6BA once after 60 frames */
    void proc_idle();               /* fn_1_10B6C idle motion */
    void setMotion(int motion, bool once); /* fn_1_10B9C (called: defined after its callers) */
    virtual void on_new_mode(int mode);
    virtual ~CHeihoMan();
    /* by value: retail copies each PTMF constant to a stack temporary before storing it (on_new_mode) */
    void setProc(ProcFunc proc) { m_proc = proc; }

    ProcFunc m_proc;           /* 0x10 (12 bytes on CW); the ctor's mem-initializer copies it directly */
    CModel m_model;            /* 0x1C body 0x46000A */
    CModel m_item;             /* 0x1E item 0x46000B, hooked at "itemhook_R" */
    int m_motion;
    std::vector<s16> m_mot_id; /* 0x24 idle, start */
    bool m_seDone;             /* 0x30 */
    int m_count;               /* 0x34 frames in proc_start (signed int->float) */
};

} // namespace m512

#ifndef __MWERKS__
template <> m512::CHeihoMan* CSingleton<m512::CHeihoMan>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
