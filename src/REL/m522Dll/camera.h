#ifndef M522_CAMERA_H
#define M522_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m522 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();                        /* fn_1_D1B4 no PerspectiveSet/ViewportSet (the motion camera has them) */
    virtual ~CCameraObj();               /* fn_1_D3D8 kills nothing (= m509 EA48) */
    virtual void on_new_mode(int mode);  /* fn_1_D4A4 */
    virtual void on_update();            /* fn_1_D60C __ptmf_test + __ptmf_scall, no counter (= m501) */
    void proc_intro();                   /* fn_1_D654 m532 proc_motion */
    void proc_idle();                    /* fn_1_D6E8 m532 proc_main */
    void Lower(float dy);                /* fn_1_D718 (stage BreakBlock, 200) */
    void proc_follow();                  /* fn_1_D798 mode 2 */
    void SetFinishView();                /* fn_1_D7F4 mode 3 */
    void SetResultView();                /* fn_1_D980 mode 4 */
    void proc_ease();                    /* fn_1_DB5C modes 3 / 4 */
    void startMotion();                  /* fn_1_DCC0 */
    void killMotion();                   /* fn_1_DD24 */
    void proc_debug();                   /* fn_1_DD5C dead (four dead stores, retail) */
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    CCamera m_camera;          /* 0x10 camera 1's view (getPos / setPos) */
    ProcFunc m_proc;           /* 0x34 (12 bytes on CW) */
    s16 m_camModel;            /* 0x40 Hu3DModelCameraCreate, -1 = none */
    int m_duration;            /* 0x44 ease length (1, 180, 120) */
    int m_frame;               /* 0x48 ease frame */
    CCameraView m_viewFrom;    /* 0x4C */
    CCameraView m_viewTo;      /* 0x68 */
    bool m_debug;              /* 0x84 dead debug toggle (Y) */
    bool m_debugHold;          /* 0x85 dead debug toggle (L) */
    CCamera m_debugCam;        /* 0x88 */
};

} // namespace m522

#ifndef __MWERKS__
template <> m522::CCameraObj* CSingleton<m522::CCameraObj>::ms_pointer; /* defined in gamemaster.cpp (bss A1C) */
#endif

#endif
