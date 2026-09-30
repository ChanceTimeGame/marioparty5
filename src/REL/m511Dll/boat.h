#ifndef M511_BOAT_H
#define M511_BOAT_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"

namespace m511 {

class CBoatMan : public CGameObject, public CSingleton<CBoatMan> {
public:
    CBoatMan();                         /* fn_1_0 four `new CBoat(s_boatModel[i], i)` (results dropped) */
    virtual ~CBoatMan();                /* fn_1_25C CBoat::DeleteAll() */
    virtual void on_update();           /* fn_1_32C CBoat::UpdateAll() */
    virtual void on_new_mode(int mode); /* fn_1_34C clear the bit; empty switch */
};

class CBoat : public TLinkItem<CBoat> {
public:
    CBoat(u32 dataNum, int no); /* fn_1_374 */
    /* fn_1_504 player updateDisp: the boat of player `no` gets pos, rot.x = rotX, rot.y = rotY */
    static void SetPos(int no, Vec* pos, float rotX, float rotY);
    static void DeleteAll();           /* fn_1_598 CBoatMan dtor: tail first, inline ~CModel/~CLinkNode */
    static void UpdateAll();           /* fn_1_66C */
    static void UpdateOne(CBoat* p);   /* fn_1_69C p->Update() */
    void Update();                     /* fn_1_6C4 setRot, setPos, ++m_time */

    static TLinkList<CBoat> s_list;    /* bss C; its DestructorChain bss 0 */

    CModel m_model; /* 0x08 0x45000D + i */
    int m_no;       /* 0x0C player index */
    Vec m_pos;      /* 0x10 SetPos */
    Vec m_rot;      /* 0x1C x = pitch, y = yaw */
    int m_time;     /* 0x28 frames */
};

} // namespace m511

#ifndef __MWERKS__
template <> m511::CBoatMan* CSingleton<m511::CBoatMan>::ms_pointer; /* defined in boat.cpp (.bss 14) */
#endif

#endif
