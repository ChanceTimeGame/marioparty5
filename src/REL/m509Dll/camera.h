/* camera.h -- m509::CCameraObj (camera.cpp): the top-down game camera (framing every player from y 4500, a
 * 60-frame zoom-in, the winner view) and the positional SE helpers every player/maze sound goes through.
 * GC: CGameObject +0x00 (vptr +8, m_execFlags +0xC), empty CSingleton<CCameraObj> at +0x10 (shares the offset
 * with m_camera), m_camera +0x10, m_count +0x34, m_proc +0x38 (12-byte PTMF), 4 untouched bytes +0x44; size 0x48
 * (gamemaster `li r3,0x48`): m512's layout without m_camModel. Vtable data_3420 {~, on_new_mode, on_update}.
 * camera.cpp does not include minigame.h; the singleton asserts are present (singleton.h:53/61). */
#ifndef M509_CAMERA_H
#define M509_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m509 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();
    /* fn_1_E1A0 / fn_1_E4B4: SE volume 104..127 and pan 0..127 of a world position (statics: no this) */
    static s16 GetSeVol(Vec* pos);
    static s16 GetSePan(Vec* pos);
    void proc_finish();  /* fn_1_E560 ease to the winner view ({0,900,500} -> {0,0,-200}) */
    void startFinish();  /* fn_1_E6E0 setProc(&proc_finish); CPlayer::StartWin, one goal player only */
    void proc_main();    /* fn_1_E724 frame every player (CPlayer::GetBounds), 60-frame zoom-in */
    void proc_debug();   /* fn_1_E86C debugView(0), Y returns to proc_main. No PTMF points here: dead */
    virtual void on_new_mode(int mode);
    virtual void on_update();
    virtual ~CCameraObj();
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    CCamera m_camera;   /* 0x10 m_pos 0x10, m_up 0x1C, m_target 0x28 */
    int m_count;        /* 0x34 frames of proc_main (zoom-in while < 60; signed) */
    ProcFunc m_proc;    /* 0x38 (12 bytes on CW) */
    int m_unk44;        /* 0x44 never read or written (sizeof 0x48) */
};

} // namespace m509

#ifndef __MWERKS__
template <> m509::CCameraObj* CSingleton<m509::CCameraObj>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
