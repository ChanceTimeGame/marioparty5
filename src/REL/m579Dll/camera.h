#ifndef M579_CAMERA_H
#define M579_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m579 {

class CPlayer;

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    CCameraObj();                          /* fn_1_8B0C m_frame left unset (retail) */
    virtual ~CCameraObj();                 /* fn_1_8D28 kills nothing (= m509 EA48 / m522 D3D8) */
    void proc_intro();                     /* fn_1_8DF4 setProc BEFORE the flag clear (m537's order is reversed) */
    void proc_idle();                      /* fn_1_8E88 (= m513 FF9C / m522 D6E8) */
    void proc_winner();                    /* fn_1_8EB8 from frame 90: lerpView 0.05 toward the winner, forever */
    void startWinnerZoom(CPlayer* p);      /* fn_1_8FCC (player FinishAll, single winner only) */
    virtual void on_new_mode(int mode);    /* fn_1_901C */
    virtual void on_update();              /* fn_1_9124 __ptmf_test + __ptmf_scall (= m501) */
    void startMotion();                    /* fn_1_916C */
    void killMotion();                     /* fn_1_91D4 */
    void proc_debug();                     /* fn_1_920C dead (no PTMF points here) */
    static s16 GetSePan(Vec* pos);         /* fn_1_9344 (= m536 6FCC) player UpdateModel */
    /* fn_1_93E4 (m536 706C with (d/100 - 14) / 11): player UpdateModel passes its m_idx in r4 (never read) */
    static s16 GetSeVol(Vec* pos, int no);
    static void PlaySe(Vec* pos, int se);  /* fn_1_9668 fishline / player / puku2 / zako */
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    CCamera m_camera;        /* 0x10 camera 1's view (getPos / setPos) */
    int m_frame;             /* 0x34 winner-zoom frame (startWinnerZoom = 0) */
    ProcFunc m_proc;         /* 0x38 (12 bytes on CW) */
    s16 m_camModel;          /* 0x44 Hu3DModelCameraCreate, -1 = none */
    CPlayer* m_target;       /* 0x48 the winner (proc_winner reads its m_pos) */
    bool m_debug;            /* 0x4C dead debug toggle (Y) */
    bool m_debugHold;        /* 0x4D dead debug toggle (L) */
    CCamera m_debugCam;      /* 0x50 */
};

} // namespace m579

#ifndef __MWERKS__
template <> m579::CCameraObj* CSingleton<m579::CCameraObj>::ms_pointer; /* defined in puku2.cpp (bss A08) */
#endif

#endif
