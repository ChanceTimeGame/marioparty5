/* camera.h -- m568::CCameraObj (camera.cpp): the one game camera (Hu3D camera bit 1). Mode 0: an intro glide from a
 * start view to the follow view over 150 frames (proc_intro), then it follows the course scroll (proc_follow);
 * mode 4: a fixed result view; thread_exec's ZoomTo smooth-steps from the current view to one aimed at a point.
 * camera.cpp does not include minigame.h (no .ctors); the singleton asserts are present (singleton.h:53/61), and it
 * reads CStage through its singleton (GetScrollZ, the floor raycast). Names are ours (W0 proposals).
 * GC: CGameObject +0x00 (vptr +8, m_execFlags +0xC), empty CSingleton<CCameraObj> at +0x10 (shares the offset with
 * m_camera), m_camera +0x10 (CCamera 0x24), m_count +0x34, m_proc +0x38 (12-byte PTMF), m_unk44 +0x44,
 * m_unk48 +0x48, (+0x4C..+0x53 never touched), m_viewFrom +0x54, m_viewTo +0x70 (CCameraView 0x1C); size 0x8C
 * (game_master `li r3,0x8C`). Vtable data_3E4 {~, on_new_mode, on_update} (+ a .data pad word).
 * CSingleton<CCameraObj>::ms_pointer is game_master.o's .bss A14. */
#ifndef M568_CAMERA_H
#define M568_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m568 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();                          /* fn_1_9D60 */
    /* fn_1_9FE8: fog + background colour, t = 0 (the only call) .. 1 */
    void SetFog(float t);
    /* fn_1_A198 / fn_1_A3F8 (unreferenced; inlined into proc_intro / proc_follow): the intro start view and the
     * follow view from the scroll z and a floor raycast */
    void GetStartView(Vec* pos, Vec* target);
    void GetGameView(Vec* pos, Vec* target);
    void proc_intro();                     /* fn_1_A664 PTMF data_3CC (mode 0) */
    void proc_follow();                    /* fn_1_AE00 PTMF data_3C0 */
    void proc_idle();                      /* fn_1_B0D0 (unreferenced) empty */
    void proc_debug();                     /* fn_1_B0D4 (unreferenced) m_camera.debugView(0) */
    virtual void on_new_mode(int mode);    /* fn_1_B104 */
    virtual void on_update();              /* fn_1_B2CC */
    void ZoomTo(Vec* at, float dist);      /* fn_1_B320 game_master thread_exec (result) */
    void proc_zoom();                      /* fn_1_B4A0 PTMF data_3D8 */
    virtual ~CCameraObj();                 /* fn_1_B59C does not kill the Hu3D camera (retail) */

    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    CCamera m_camera;         /* 0x10 */
    int m_count;
    ProcFunc m_proc;          /* 0x38 (12 bytes on CW) */
    int m_unk44;              /* 0x44 = 0, never read */
    int m_unk48;              /* 0x48 = 0, never read */
    u8 m_unk4C[8];            /* 0x4C never touched */
    CCameraView m_viewFrom;   /* 0x54 */
    CCameraView m_viewTo;     /* 0x70 */
};

} // namespace m568

#ifndef __MWERKS__
template <> m568::CCameraObj* CSingleton<m568::CCameraObj>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
