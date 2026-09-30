#ifndef M511_CAMERA_H
#define M511_CAMERA_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/camera.h"

namespace m511 {

class CCameraObj : public CGameObject, public CSingleton<CCameraObj> {
public:
    typedef void (CCameraObj::*ProcFunc)();

    /* one player's quadrant (GC 0x44; name ours). +0x2C, +0x38, +0x3C are never referenced. */
    struct SubCam {
        CCamera cam;    /* 0x00 pos +0, up +0xC, target +0x18 */
        float x;        /* 0x24 viewport (640x480 units) */
        float y;        /* 0x28 */
        float m_unk2C;  /* 0x2C */
        float w;        /* 0x30 */
        float h;        /* 0x34 */
        float m_unk38;  /* 0x38 */
        float m_unk3C;  /* 0x3C */
        bool active;    /* 0x40 the Hu3D camera exists */
    };

    CCameraObj();                                        /* fn_1_97C8 */
    void setViewport(int i, float x, float y, float w, float h); /* fn_1_9A98 clamp; create/kill; set */
    void setSplit(float cx, float cy);                   /* fn_1_9DA8 unreferenced: the four quadrants */
    void smooth(int i, Vec* target, Vec* pos);           /* fn_1_9F98 unreferenced */
    void getFollow(int i, Vec* target, Vec* pos);        /* fn_1_A060 unreferenced (CPlayer::GetCameraPos) */
    void getFollowResult(int i, Vec* target, Vec* pos);  /* fn_1_A16C unreferenced (GetFrontCameraPos) */
    void follow();                                       /* inline in camera.cpp (proc_split's loop) */
    void proc_follow0();                                 /* fn_1_A278 the ctor's proc */
    void proc_follow();                                  /* fn_1_A3B4 identical body */
    void proc_debug();                                   /* fn_1_A4F0 unreachable (no PTMF): fw debugView */
    void proc_split();                                   /* fn_1_A580 intro: quadrant 0 shrinks, 60 f */
    void proc_intro();                                   /* fn_1_ABA8 camera motion */
    void proc_result();                                  /* fn_1_AD04 the winner's quadrant grows, 120 f */
    void setWinner(int no);                              /* fn_1_B2D4 player CheckGameEnd */
    virtual void on_new_mode(int mode);                  /* fn_1_B324 */
    virtual void on_update();                            /* fn_1_B4C0 */
    static s16 GetPan(const Vec* pos, int pno);          /* fn_1_B508 unreferenced */
    static int PlaySe(const Vec* pos, int seNo, int pno);     /* fn_1_B6C0 player engine loops */
    static int PlaySePlay(const Vec* pos, int seNo, int pno); /* fn_1_B864 mode 2 only, else -1 */
    static void UpdateSe(const Vec* pos, int handle, int pno, float pitch); /* fn_1_BA18 pan/pitch/volume */
    virtual ~CCameraObj();                               /* fn_1_BC4C kills no Hu3D camera (retail) */
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    Vec m_split;             /* 0x010 split point x, y (z never referenced) */
    SubCam m_cam[4];         /* 0x01C */
    CCamera m_debugCam;      /* 0x12C */
    int m_count;             /* 0x150 frames in the current proc */
    ProcFunc m_proc;         /* 0x154 (12 bytes on CW) */
    HU3DMODELID m_camModel;  /* 0x160 Hu3DModelCameraCreate */
    int m_winner;            /* 0x164 -1 until setWinner */
};

} // namespace m511

#ifndef __MWERKS__
template <> m511::CCameraObj* CSingleton<m511::CCameraObj>::ms_pointer; /* defined in gamemaster.cpp (.bss A3C) */
#endif

#endif
