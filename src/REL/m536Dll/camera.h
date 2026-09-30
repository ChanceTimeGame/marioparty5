/* camera.h -- m536::CCameraObj (camera.cpp): the game camera (intro motion 0x5E0007, idle, winner zoom) and
 * the SE pan/volume helpers every player sound goes through.
 * GC: CGameObject +0x00 (vptr +8, m_execFlags +0xC), empty CSingleton<CCameraObj> at +0x10 (shares the offset
 * with m_camera), m_camera +0x10, m_count +0x34, m_proc +0x38 (12-byte PTMF), m_camModel +0x44, m_se +0x48;
 * size 0x4C (game_master `li r3,0x4C`).
 * camera.cpp does not include minigame.h (no 120/210/210 triple in camera.o); unlike m501's camera.cpp it
 * keeps the singleton asserts (singleton.h:53/61 strings are in camera .data). */
#ifndef M536_CAMERA_H
#define M536_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m536 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();
    void proc_idle();       /* fn_1_6954 Hu3DCameraPosSetV(1, pos, up, target); also called by the ctor */
    void proc_debug();      /* fn_1_69B4 debugView(0), Y returns to proc_idle. No PTMF points here: dead */
    void proc_move();       /* fn_1_6A70 mode 0: intro camera motion; the SE fades 127 -> 88 */
    void proc_zoom();       /* fn_1_6C74 ease to the winner view ({0,600,400} -> {0,0,-100}) */
    void startWinnerZoom(); /* fn_1_6DF4 setProc(&proc_zoom); CPlayer::SetRank, one survivor */
    virtual void on_new_mode(int mode);
    virtual void on_update();
    /* fn_1_6FCC / fn_1_706C: SE pan 0..127 and volume 96..127 of a world position (statics: no this) */
    static s16 GetSePan(Vec* pos);
    static s16 GetSeVol(Vec* pos);
    virtual ~CCameraObj();
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    CCamera m_camera;        /* 0x10 m_pos 0x10, m_up 0x1C, m_target 0x28 */
    int m_count;             /* 0x34 */
    ProcFunc m_proc;         /* 0x38 (12 bytes on CW) */
    HU3DMODELID m_camModel;  /* 0x44 Hu3DModelCameraCreate */
    int m_se;                /* 0x48 HuAudFXPlayVol(0x7D7, 0x7F); never stopped (retail) */
};

} // namespace m536

#ifndef __MWERKS__
template <> m536::CCameraObj* CSingleton<m536::CCameraObj>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
