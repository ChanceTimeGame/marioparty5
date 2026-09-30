/* camera.h -- m517::CCameraObj (camera.cpp): the game camera (Hu3D camera 1). Mode 0 plays the intro camera motion
 * (0x4B0000) and keeps its end view; mode 3 eases to the finish view (the far one, or the near one when the solo won:
 * gamemaster sets m_final). Names ours (master_camera_stage_misc_audio.md §4).
 * GC 0x80 (gamemaster `li r3,0x80`): CGameObject +0x00, empty CSingleton<CCameraObj> +0x10 (ms_pointer = gamemaster.o
 * .bss A20), m_camera +0x10, m_from +0x34 / m_to +0x50 / m_frame +0x6C (never accessed: m521's members, kept for the
 * size), m_proc +0x70, m_final +0x7C, m_camModel +0x7E. Vtable data_4DC {~, on_new_mode, on_update}.
 * camera.cpp includes no minigame.h, player.h or util.h. */
#ifndef M517_CAMERA_H
#define M517_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m517 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();                       /* fn_1_DC4C */
    void proc_idle();                   /* fn_1_DE68 */
    void proc_intro();                  /* fn_1_DE98 (mode 0) */
    void proc_ease();                   /* fn_1_DF28 (mode 3) */
    virtual void on_new_mode(int mode); /* fn_1_E11C */
    virtual void on_update();           /* fn_1_E290 */
    virtual ~CCameraObj();              /* fn_1_E2D8 */

    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }
    /* gamemaster thread_exec (the solo won) */
    void SetFinal() { m_final = true; }

    CCamera m_camera;       /* 0x10 m_pos 0x10, m_up 0x1C, m_target 0x28 */
    CCameraView m_from;     /* 0x34 never accessed */
    CCameraView m_to;       /* 0x50 never accessed */
    int m_frame;            /* 0x6C never accessed */
    ProcFunc m_proc;        /* 0x70 (12 bytes on CW) */
    bool m_final;           /* 0x7C the finish view: near (solo won) / far */
    HU3DMODELID m_camModel;
};

} // namespace m517

#ifndef __MWERKS__
template <> m517::CCameraObj* CSingleton<m517::CCameraObj>::ms_pointer; /* defined in gamemaster.cpp (A20) */
#endif

#endif
