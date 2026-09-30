/* camera.h -- m521::CCameraObj (camera.cpp): the fixed game camera (a motion camera 0x4F000E in mode 0, released in
 * mode 1) and the winner zoom (startWinnerZoom: a 150-frame smoothstep from s_winView, mirrored for red).
 * GC 0x80 (gamemaster `li r3,0x80`): CGameObject +0x00, empty CSingleton<CCameraObj> +0x10, m_camera +0x10,
 * m_from +0x34, m_to +0x50, m_frame +0x6C, m_proc +0x70, m_camModel +0x7C. Vtable data_5B8 {~, on_new_mode,
 * on_update}. camera.cpp includes no minigame.h. Names ours (sheet §4). */
#ifndef M521_CAMERA_H
#define M521_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m521 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();                      /* fn_1_1416C (the ~CSingleton / ~CLinkItem weak copies follow it) */
    void proc_idle();                  /* fn_1_143D0 */
    void proc_intro();                 /* fn_1_143D4 */
    virtual void on_new_mode(int mode); /* fn_1_14424 */
    virtual void on_update();          /* fn_1_145A4 */
    void startWinnerZoom(int team);    /* fn_1_145F8 (gamemaster) */
    void proc_zoom();                  /* fn_1_14744 */
    virtual ~CCameraObj();             /* fn_1_14840 (m_camModel not killed: retail) */
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    CCamera m_camera;       /* 0x10 never constructed (filled by getPos / lerpView) */
    CCameraView m_from;     /* 0x34 */
    CCameraView m_to;       /* 0x50 */
    int m_frame;
    ProcFunc m_proc;        /* 0x70 */
    HU3DMODELID m_camModel; /* 0x7C */
};

} // namespace m521

#ifndef __MWERKS__
template <> m521::CCameraObj* CSingleton<m521::CCameraObj>::ms_pointer; /* defined in gamemaster.cpp (A7C) */
#endif

#endif
