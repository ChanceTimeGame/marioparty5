/* camera.h -- m512::CCameraObj (camera.cpp): the game camera (intro motion 0x460012, a follow camera framing
 * every player, an immediate race view, the winner zoom) and the positional SE helpers every player sound
 * goes through.
 * GC: CGameObject +0x00 (vptr +8, m_execFlags +0xC), empty CSingleton<CCameraObj> at +0x10 (shares the offset
 * with m_camera), m_camera +0x10, m_count +0x34, m_proc +0x38 (12-byte PTMF), m_camModel +0x44; size 0x48
 * (gamemaster `li r3,0x48`): m536's layout minus m_se.
 * camera.cpp does not include minigame.h; the singleton asserts are present (singleton.h:53/61). */
#ifndef M512_CAMERA_H
#define M512_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m512 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();
    void getView(Vec* center, Vec* eye);
    void proc_follow();     /* fn_1_6C98 ease to getView (the ctor's proc, also called by it) */
    void proc_play();       /* fn_1_6F0C mode 2: getView set immediately (m_pos/m_target untouched) */
    void proc_debug();      /* fn_1_7074 debugView(0), Y returns to proc_follow. No PTMF points here: dead */
    void proc_move();       /* fn_1_7130 mode 0: intro camera motion */
    void proc_zoom();       /* fn_1_7214 ease around the winner (CPlayer::GetWinnerPos) */
    void startWinnerZoom(); /* fn_1_7488 setProc(&proc_zoom); CPlayer::CheckGameEnd, normal mode */
    virtual void on_new_mode(int mode);
    virtual void on_update();
    /* fn_1_76BC: plays se at pos (pan from the screen x) in update mode 2 only; ALWAYS returns -1 (retail) */
    static int PlaySe(Vec* pos, int se);
    /* fn_1_7708: HuAudFXPlay + HuAudFXPanning(pan 0..127); returns the handle */
    static int PlaySePan(Vec* pos, int se);
    virtual ~CCameraObj();
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    CCamera m_camera;        /* 0x10 m_pos 0x10, m_up 0x1C, m_target 0x28 */
    int m_count;             /* 0x34 ++ in proc_move only; never compared */
    ProcFunc m_proc;         /* 0x38 (12 bytes on CW) */
    HU3DMODELID m_camModel;  /* 0x44 Hu3DModelCameraCreate */
};

} // namespace m512

#ifndef __MWERKS__
template <> m512::CCameraObj* CSingleton<m512::CCameraObj>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
