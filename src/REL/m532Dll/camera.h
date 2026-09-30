/* camera.h -- m532::CCameraObj (camera.cpp): the motion camera. Mode 0 plays the camera motion 0x5A0000 on
 * camera 1 (startMotion) and holds its last frame afterwards (proc_main); mode 1 kills the motion model. A dead
 * debug camera (proc_debug: no PTMF, no caller) keeps its own CCamera.
 * GC: CGameObject +0 (vptr +8, m_execFlags +0xC), empty CSingleton<CCameraObj> +0x10 (shares the offset with
 * m_camera), m_camera +0x10, m_proc +0x34 (12-byte PTMF), m_camModel +0x40, m_count +0x44, m_unkView +0x48
 * (0x38 bytes never touched: two CCameraView, a guess), m_debug +0x80, m_debugHold +0x81, m_debugCam +0x84;
 * size 0xA8 (game_master `li r3,0xA8`). Vtable data_3E8 {~ 98B0, on_new_mode 997C, on_update 9A84} + a pad word.
 * ms_pointer = game_master.o bss_A2C (only camera.cpp uses it). camera.cpp includes neither minigame.h nor
 * param.h (no .ctors). Names are ours. */
#ifndef M532_CAMERA_H
#define M532_CAMERA_H

#include "REL/m532Dll/config.h"
#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m532 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();                        /* fn_1_96EC no PerspectiveSet/ViewportSet (the motion camera has them) */
    virtual ~CCameraObj();               /* fn_1_98B0 kills nothing (m509 EA48's shape) */
    virtual void on_new_mode(int mode);  /* fn_1_997C 0: startMotion + proc_motion (bit cleared by proc_motion) */
    virtual void on_update();            /* fn_1_9A84 */
    void proc_motion();                  /* fn_1_9AD8 follows the motion; at its end clears bit 0, proc_main */
    void proc_main();                    /* fn_1_9B6C holds the last motion frame */
    void startMotion();
    void killMotion();                   /* fn_1_9C00 */
    void proc_debug();                   /* fn_1_9C38 dead (four dead stores, retail) */
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    CCamera m_camera;          /* 0x10 camera 1's view (getPos / setPos) */
    ProcFunc m_proc;           /* 0x34 (12 bytes on CW) */
    s16 m_camModel;            /* 0x40 Hu3DModelCameraCreate, -1 = none */
    int m_count;               /* 0x44 ++ per on_update, never read */
    CCameraView m_unkView[2];  /* 0x48 never touched (fits two CCameraView, sheet guess) */
    bool m_debug;              /* 0x80 dead debug toggle (Y) */
    bool m_debugHold;          /* 0x81 dead debug toggle (L) */
    CCamera m_debugCam;        /* 0x84 */
};

} // namespace m532

#ifndef __MWERKS__
template <> m532::CCameraObj* CSingleton<m532::CCameraObj>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
