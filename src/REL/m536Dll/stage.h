/* stage.h -- the stage (stage.cpp): m536::CStage (arena models, fog hooks, the random cannon-smoke timer),
 * m536::CCloud (four drifting clouds) and m536::CStageCannon (the eight cannon-smoke model links).
 * stage.cpp does not include minigame.h (its __sinit only builds CStageCannon::list); the singleton asserts
 * are present. Class names CCloud/CStageCannon are ours (W0 guesses). */
#ifndef M536_STAGE_H
#define M536_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"

namespace m536 {

/* GC: CGameObject +0x00, empty CSingleton<CStage> at +0x10, CModels +0x10..+0x18, m_fireTimer[4] +0x1C;
 * size 0x2C (game_master `li r3,0x2C`). Vtable data_3B0 {~, on_new_mode, on_update}. */
class CStage : public CGameObject, public CSingleton<CStage> {
public:
    CStage();
    virtual void on_update();
    virtual void on_new_mode(int mode);
    virtual ~CStage();

    CModel m_bgModel;     /* 0x10 data 0x5E0000: layer 1, LightInfoSet, loop motion */
    CModel m_model1;      /* 0x12 data 0x5E0001: layer 1, loop motion */
    CModel m_skyModel;    /* 0x14 data 0x5E0002: layer 0 (drawn before the fog hook) */
    CModel m_smokeTmplA;  /* 0x16 data 0x5E0004 DISPOFF: template of the even CStageCannon links */
    CModel m_smokeTmplB;  /* 0x18 data 0x5E0005 DISPOFF: template of the odd links */
    int m_fireTimer[4];   /* 0x1C per corner: frames to the next random smoke (signed) */
};

/* GC: CGameObject +0x00, empty CSingleton<CCloud> at +0x10, m_model +0x10, m_ids[4] +0x12, m_pos[4] +0x1C;
 * size 0x4C (game_master `li r3,0x4C` at 61E0). Vtable data_39C. */
class CCloud : public CGameObject, public CSingleton<CCloud> {
public:
    CCloud();
    virtual void on_update();
    virtual void on_new_mode(int mode);
    virtual ~CCloud();

    CModel m_model;       /* 0x10 data 0x5E0003 */
    HU3DMODELID m_ids[4]; /* 0x12 [0] = m_model's id, [1..3] = Hu3DModelLink(m_model) (never killed: retail) */
    Vec m_pos[4];         /* 0x1C */
};

/* A plain list item (no vptr). GC: TLinkItem (CLinkNode) +0x0, m_model +0x8, m_index +0xC; size 0x10.
 * CStage's ctor makes eight (two per corner); Fire(i) plays the i-th once. */
class CStageCannon : public TLinkItem<CStageCannon> {
public:
    CStageCannon(CModel& tmpl, int index, float rotY);
    static void Close();                        /* fn_1_95DC never called (retail) */
    static void UpdateAll();                    /* fn_1_96B0 never called (retail) */
    static void UpdateOne(CStageCannon* p);     /* fn_1_96E0 */
    static void Fire(int index);                /* fn_1_9744 */

    static TLinkList<CStageCannon> list;        /* bss A74; its DestructorChain A68 */

    CModel m_model;  /* 0x08 Hu3DModelLink of the template */
    int m_index;     /* 0x0C 0..7 (signed compare) */
};

} // namespace m536

#ifndef __MWERKS__
template <> m536::CStage* CSingleton<m536::CStage>::ms_pointer; /* defined in game_master.cpp */
template <> m536::CCloud* CSingleton<m536::CCloud>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
