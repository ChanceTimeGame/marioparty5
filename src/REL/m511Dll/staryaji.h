#ifndef M511_STARYAJI_H
#define M511_STARYAJI_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/tlink.h"

namespace m511 {

class CStarYajiMan : public CGameObject, public CSingleton<CStarYajiMan> {
public:
    CStarYajiMan();                     /* fn_1_E8BC */
    virtual ~CStarYajiMan();            /* fn_1_EA18 CStarYaji::DeleteAll() */
    virtual void on_new_mode(int mode); /* fn_1_EAE8 */
    virtual void on_update();           /* fn_1_EB00 CStarYaji::UpdateAll() */
};

class CStarYaji : public TLinkItem<CStarYaji> {
public:
    static void DrawHook(HU3DMODEL* model, Mtx* mtx); /* fn_1_EB20 visible && hasTarget -> Draw */
    CStarYaji(int player, int charNo);                /* fn_1_EB7C player ctor */
    ~CStarYaji();                                     /* fn_1_ED70 unreferenced (inlined in DeleteAll) */
    static void DeleteAll();                          /* fn_1_EDD8 */
    static void UpdateAll();                          /* fn_1_EEA8 */
    /* fn_1_EED8 player UpdateCourse: the arrow of `player` points from pos at star `gate` */
    static void SetTarget(int player, Vec* pos, int gate, float heading);
    static void ShowAll();                            /* fn_1_F010 gamemaster (mode 2) */
    static void HideAll();                            /* fn_1_F074 gamemaster (mode 3) */
    static void Hide(int player);                     /* fn_1_F0D8 player at the goal */
    static void Update(CStarYaji* p);                 /* fn_1_F148 */
    void SetupGX();                                   /* fn_1_F2C8 unreferenced (inlined in Draw) */
    void Draw(Mtx* mtx);                              /* fn_1_F47C */

    static TLinkList<CStarYaji> list; /* bss A9C; its DestructorChain A90 */

    bool m_visible;      /* 0x08 */
    bool m_hasTarget;    /* 0x09 */
    float m_rotY;        /* 0x0C heading to the target (deg) */
    float m_heading;     /* 0x10 player heading (SetTarget) */
    Vec m_pos;           /* 0x14 player position (SetTarget) */
    float m_alpha;       /* 0x20 0..192 */
    int m_target;        /* 0x24 gate index; 5 = goal (pulse) */
    HU3DMODELID m_model; /* 0x28 Hu3DHookFuncCreate(DrawHook) */
    int m_frame;         /* 0x2C */
    int m_player;        /* 0x30 camera mask 1 << player */
    int m_charNo;        /* 0x34 write-only */
    ANIMDATA* m_anim;    /* 0x38 CEffTex::m_yajiAnim (borrowed) */
};

} // namespace m511

#ifndef __MWERKS__
template <> m511::CStarYajiMan* CSingleton<m511::CStarYajiMan>::ms_pointer; /* defined in gamemaster.cpp (.bss A34) */
#endif

#endif
