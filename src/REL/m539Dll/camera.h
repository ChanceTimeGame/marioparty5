/* camera.h -- m539::CCameraObj (camera.cpp): four player cameras (Hu3DCameraCreate(0xF)) that start as one
 * full-screen view and split into four quadrants over 60 frames after frame 300 of mode 0 (proc_split);
 * two CCamera views (top and bottom row) re-applied every frame. camera.cpp does not include minigame.h; the
 * singleton asserts are present (singleton.h:53/61).
 * GC: CGameObject +0x00 (vptr +8, m_execFlags +0xC), empty CSingleton<CCameraObj> at +0x10 (shares the offset
 * with m_camera), m_camera[2] +0x10/+0x34, m_count +0x58, m_proc +0x5C (12-byte PTMF), m_unk68 +0x68; size 0x6C
 * (game_master `li r3,0x6C`). Vtable data_398 {~, on_new_mode, on_update} (+ a .data pad word). */
#ifndef M539_CAMERA_H
#define M539_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m539 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    /* fn_1_A310 (unreferenced; inlined 4x into SetSplitScreen): camera `cam` perspective + viewport + scissor
     * over (x0,y0)-(x1,y1); a negative width or height switches the camera off (fov -1) */
    static void SetViewport(int cam, float x0, float y0, float x1, float y1);
    /* fn_1_A4D0 (unreferenced; inlined into the ctor and proc_split): the four quadrants at scale s (s = 2:
     * camera 0 full-screen, 1..3 off; s = 1: four quadrants). cam 3's right edge is 639, cam 1's 640 (retail) */
    static void SetSplitScreen(float s);
    CCameraObj();                         /* fn_1_AB68 */
    void proc_idle();                     /* fn_1_B3C0 empty (mode 1) */
    /* fn_1_B3C4 mode 0: after frame 300, SetSplitScreen(t + 2(1 - t)) over 60 frames, then clears exec bit 0 */
    void proc_split();
    virtual void on_new_mode(int mode);   /* fn_1_BB14 */
    virtual void on_update();             /* fn_1_BC24 */
    virtual ~CCameraObj();                /* fn_1_BDF0 does not kill the cameras (retail) */
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    CCamera m_camera[2]; /* 0x10 top row (camera bits 0|1), 0x34 bottom row (2|3) */
    int m_count;
    ProcFunc m_proc;     /* 0x5C (12 bytes on CW) */
    int m_unk68;         /* 0x68 never accessed */
};

} // namespace m539

#ifndef __MWERKS__
template <> m539::CCameraObj* CSingleton<m539::CCameraObj>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
