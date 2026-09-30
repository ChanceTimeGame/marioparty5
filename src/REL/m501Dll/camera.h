/* camera.h -- m501::CCameraObj (camera.cpp): the game camera object (intro move-up, idle, winner focus).
 * GC: CGameObject +0x00 (vptr +8), empty CSingleton<CCameraObj> at +0x10 (shares the offset with
 * m_camera), m_camera +0x10, m_from +0x34, m_to +0x50, m_count +0x6C, m_proc +0x70 (12-byte PTMF),
 * m_camModel +0x7C; size 0x80.
 * camera.cpp does not include minigame.h (no 120/210/210 triple in camera.o). */
#ifndef M501_CAMERA_H
#define M501_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m501 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();
    void set_focus_player(Vec* pos);
    void proc_focus_player();
    void proc_null();
    void proc_move_up();
    void proc_idle();
    virtual void on_new_mode(int mode);
    virtual void on_update();
    virtual ~CCameraObj();
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    CCamera m_camera;      /* 0x10 */
    CCameraView m_from;    /* 0x34 */
    CCameraView m_to;      /* 0x50 */
    int m_count;           /* 0x6C */
    ProcFunc m_proc;       /* 0x70 */
    HU3DMODELID m_camModel; /* 0x7C Hu3DModelCameraCreate */
};

} // namespace m501

#ifndef __MWERKS__
template <> m501::CCameraObj* CSingleton<m501::CCameraObj>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
