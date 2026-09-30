/* camera.h -- m513::CCameraObj (camera.cpp): the game camera (Hu3D camera 1). Mode 0 plays the intro camera
 * motion (0x470003) and keeps its end view; mode 3 eases back to it; m_yaw (read by the players to face the
 * camera) follows the view direction. Names are ours.
 * GC (0x60, gamemaster `li r3,0x60`; vtable data_748 {~, on_new_mode, on_update} + pad): CGameObject +0x00,
 * empty CSingleton<CCameraObj> +0x10 (ms_pointer = gamemaster.o .bss A18; shares the offset with m_camera),
 * m_camera +0x10 (CCamera 0x24), m_proc +0x34, m_camModel +0x40, m_yaw +0x44, m_goalPos +0x48, m_goalTarget +0x54.
 * camera.cpp does not include minigame.h or player.h. */
#ifndef M513_CAMERA_H
#define M513_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m513 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();                       /* fn_1_FD60 */
    void proc_idle();                   /* fn_1_FF9C PTMF data_6EC / 724 */
    void proc_intro();                  /* fn_1_FFCC PTMF data_730 (mode 0) */
    void proc_ease();                   /* fn_1_1008C PTMF data_73C (mode 3) */
    virtual void on_new_mode(int mode); /* fn_1_101E0 */
    virtual void on_update();           /* fn_1_10358 */
    virtual ~CCameraObj();              /* fn_1_103E4 */

    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }
    /* read by CPlayer (singleton + 0x44) */
    float GetYaw() const { return m_yaw; }

    CCamera m_camera;         /* 0x10 m_pos 0x10, m_up 0x1C, m_target 0x28 */
    ProcFunc m_proc;          /* 0x34 (12 bytes on CW) */
    HU3DMODELID m_camModel;
    float m_yaw;              /* 0x44 degrees */
    Vec m_goalPos;            /* 0x48 the view at the end of the intro */
    Vec m_goalTarget;         /* 0x54 */
};

} // namespace m513

#ifndef __MWERKS__
template <> m513::CCameraObj* CSingleton<m513::CCameraObj>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
