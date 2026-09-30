/* kibako.h -- kibako.cpp (.text 18A9C..19804, .data 678..6C8, .bss B00..B18): the six floating wooden crates
 * (kibako) that stun a boat (boat_water_kibako.md §2.5).
 * m511::CKibakoMan GC 0x14 (gamemaster `li r3,0x14`): CGameObject + empty CSingleton<CKibakoMan> (+0x10, ms_pointer =
 *   gamemaster.o bss A30) + the hidden template model m_model +0x10. Vtable data_6B0 {~ 18C10, on_new_mode 18ED4,
 *   on_update 18EB4} (+ pad word). Create() places the crates (gamemaster thread_exec) and printf's each (retail).
 * m511::CKibako GC 0x38 (`li r3,0x38`): TLinkItem<CKibako> in the static list (bss B0C, chain B00); never removed
 *   before DeleteAll. Hit() (player hitCheck) hits EVERY crate in range (retail). */
#ifndef M511_KIBAKO_H
#define M511_KIBAKO_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m511Dll/boatsplash.h"
#include <memory>

namespace m511 {

class CWater;

class CKibakoMan : public CGameObject, public CSingleton<CKibakoMan> {
public:
    CKibakoMan();                       /* fn_1_18A9C */
    virtual ~CKibakoMan();              /* fn_1_18C10 CKibako::DeleteAll() */
    void Create();                      /* fn_1_18CEC gamemaster thread_exec: six crates round stars 1..3 */
    virtual void on_update();           /* fn_1_18EB4 CKibako::UpdateAll() */
    virtual void on_new_mode(int mode); /* fn_1_18ED4 */

    CModel m_model; /* 0x10 0x450020, hidden (passed to CKibako, unused there) */
};

class CKibako : public TLinkItem<CKibako> {
public:
    CKibako(CModel* src, const Vec* pos);        /* fn_1_18EFC src unused */
    static bool Hit(const Vec* pos, int player); /* fn_1_19190 player hitCheck: 200x200 box, no break */
    static void DeleteAll();                     /* fn_1_19364 */
    static void UpdateAll();                     /* fn_1_19450 */
    static void UpdateOne(CKibako* p);           /* fn_1_19480 floating ? Float() : Break(); updateModel() */
    void Float();                                /* fn_1_194D0 */
    void Break();                                /* fn_1_1952C blink 60 frames, splash + SE at 43 */
    void updateModel();                          /* fn_1_19648 */

    static TLinkList<CKibako> s_list; /* bss B0C; its DestructorChain B00 */

    bool m_floating;                         /* 0x08 1; Hit clears */
    CModel m_model;                          /* 0x0A 0x450020 */
    Vec m_pos;                               /* 0x0C */
    Vec m_rot;                               /* 0x18 */
    int m_time;                              /* 0x24 */
    bool m_splashed;                         /* 0x28 */
    int m_hitPlayer;                         /* 0x2C SE index */
    CWater* m_water;                         /* 0x30 CWater::GetInstance() */
    std::auto_ptr<CKibakoSplash> m_splash;   /* 0x34 */
};

} // namespace m511

#ifndef __MWERKS__
template <> m511::CKibakoMan* CSingleton<m511::CKibakoMan>::ms_pointer; /* defined in gamemaster.cpp (.bss A30) */
#endif

#endif
