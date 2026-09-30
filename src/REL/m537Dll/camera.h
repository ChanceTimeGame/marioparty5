#ifndef M537_CAMERA_H
#define M537_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m537 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();                        /* fn_1_8964 no PerspectiveSet/ViewportSet (the motion camera has them) */
    virtual ~CCameraObj();               /* fn_1_8B30 kills nothing (= m522 D3D8) */
    virtual void on_new_mode(int mode);  /* fn_1_8BFC */
    virtual void on_update();            /* fn_1_8D0C __ptmf_test + __ptmf_scall (= m501) */
    void proc_intro();                   /* fn_1_8D54 (= m522 D654) */
    void proc_idle();                    /* fn_1_8DE8 (= m522 D6E8) */
    void SetWinnerView();                /* fn_1_8E18 mode 3 */
    void proc_ease();                    /* fn_1_8F4C */
    void startMotion();                  /* fn_1_90B0 */
    void killMotion();                   /* fn_1_9114 (= m522 DD24) */
    void proc_debug();                   /* fn_1_914C dead (four dead stores, retail) */
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    CCamera m_camera;          /* 0x10 camera 1's view (getPos / setPos) */
    ProcFunc m_proc;           /* 0x34 (12 bytes on CW) */
    s16 m_camModel;            /* 0x40 Hu3DModelCameraCreate, -1 = none */
    double m_duration;         /* 0x48 ease length, 180.0 (never changed) */
    int m_frame;               /* 0x50 ease frame (not set by the ctor) */
    CCameraView m_viewFrom;    /* 0x54 */
    CCameraView m_viewTo;      /* 0x70 */
    bool m_debug;              /* 0x8C dead debug toggle (Y) */
    bool m_debugHold;          /* 0x8D dead debug toggle (L) */
    CCamera m_debugCam;        /* 0x90 */
};

} // namespace m537

#ifndef __MWERKS__
template <> m537::CCameraObj* CSingleton<m537::CCameraObj>::ms_pointer; /* defined in game_master.cpp (bss A10) */
#endif

#endif
