/* kuribo.h -- kuribo.cpp: m517::CKuribo, one of the two background Goombas the stage creates (fire and forget: on
 * ObjectList only, deleted by CGameObject::Close through the virtual dtor). Type 0 wanders (wait, turn 177 deg,
 * walk 4 s), types 1 / 2 look around (swing +-44 deg); -1 would freeze it. A CShadow follows it. Names ours
 * (player_kuribo.md §2.1).
 * GC 0x58 (stage `li r3,0x58`): CModel BASE +0x00 (~CModel(this, 0): a base), CGameObject +0x04 (CLinkNode +4,
 * its vptr +0xC, m_execFlags +0x10), m_mot_id +0x14, m_shadow +0x20, m_motion +0x24, m_timer +0x28, m_type
 * +0x2C, m_pos +0x30, m_rot +0x3C, m_state +0x48, m_wait +0x4C, m_dir +0x50, CKuribo's own vptr +0x54 (every
 * data member is declared before the first virtual: m522 / m531 / m532 trailing-vptr rule). Vtable .data 400
 * (0x28): {0, 0, [CGameObject-in-CKuribo: 0, 0, thunk ~, thunk on_new_mode, thunk on_update], ~CKuribo,
 * on_new_mode, on_update}; the thunks (DBA0 / DBA8 / DBB0) are CW's (-4). kuribo.cpp does not include player.h,
 * util.h or minigame.h (no PTMF triple, no zero block, no .ctors). */
#ifndef M517_KURIBO_H
#define M517_KURIBO_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/model.h"
#include "REL/m517Dll/dusteff.h"
#include <memory>
#include <vector>

namespace m517 {

class CKuribo : public CModel, public CGameObject {
public:
    enum { MOT_IDLE = 0, MOT_WALK = 1 };

    CKuribo(Vec* pos, Vec* rot, int type); /* fn_1_C994 (stage) */
    void LightSet(s16 model);              /* fn_1_CF08 dead (unreferenced member; `this` unused) */
    void AmbSet(s16 model);                /* fn_1_CFD4 dead */
    void procWalk();                       /* fn_1_D038 (unreferenced; inlined in on_update) */
    void procLook();                       /* fn_1_D1FC (unreferenced; inlined in on_update) */
    void addMotion(int dataNum);           /* fn_1_D658 */
    void setMotion(int no);                /* fn_1_D6E4 compares m_motion (an index) with the id: retail */

    std::vector<s16> m_mot_id;          /* 0x14 no reserve */
    std::auto_ptr<CShadow> m_shadow;    /* 0x20 */
    int m_motion;                       /* 0x24 index */
    int m_timer;                        /* 0x28 frames (+1 per update) */
    int m_type;                         /* 0x2C 0 walker, 1 / 2 looker, -1 frozen */
    Vec m_pos;                          /* 0x30 */
    Vec m_rot;                          /* 0x3C degrees */
    int m_state;                        /* 0x48 */
    int m_wait;                         /* 0x4C frames: (frand() % 5) * 60 */
    int m_dir;                          /* 0x50 0 / 1 (not set for type -1: retail) */

    virtual ~CKuribo();                 /* fn_1_CDF0 (thunk fn_1_DBB0) */
    virtual void on_new_mode(int mode); /* fn_1_D020 (thunk fn_1_DBA8) */
    virtual void on_update();           /* fn_1_D31C (thunk fn_1_DBA0) */
};

} // namespace m517

#endif
