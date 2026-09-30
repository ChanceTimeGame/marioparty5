#ifndef M532_MAN_OBJECT_H
#define M532_MAN_OBJECT_H

#include "REL/m532Dll/config.h"
#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/handle.h"
#include "REL/mgcpp/tlink.h"

namespace m532 {

class CObjectMan : public CGameObject, public CSingleton<CObjectMan> {
public:
    CObjectMan(CHandleMan* handleMan);   /* fn_1_E54C */
    virtual ~CObjectMan();               /* fn_1_E6C4 CObject::DeleteAll (= m539 scorespr F150 modulo names) */
    virtual void on_new_mode(int mode);  /* fn_1_E794 mode 3: CObject::FinishAll */
    virtual void on_update();            /* fn_1_E810 CObject::UpdateAll */

    CHandleMan* m_handleMan;             /* 0x10 game_master's m_handleMan; also CObject::s_handleMan */
};

class CObject : public TLinkItem<CObject>, public CModel {
public:
    typedef void (*ExecFunc)(CObject* o);

    /* the vtable slot order is DECLARATION order ({~, update, draw, onFinish}); definition order is retail's */
    virtual ~CObject();                              /* fn_1_EAF0 key function: the vtable is man_object.o's */
    static void UpdateAll();                         /* fn_1_E830 execList(&s_list, Update) (= m539 F55C) */
    static void Update(CObject* o);                  /* fn_1_E860 o->update() */
    virtual void update();                           /* fn_1_E894 empty */
    static void HookFunc(HU3DMODEL* model, Mtx* mtx); /* fn_1_E898 ((CObject*)model->hookData)->draw(mtx) */
    static void FinishAll();                         /* fn_1_E8DC TLinkList exec (plain walk) of Finish */
    static void Finish(CObject* o);                  /* fn_1_E90C o->onFinish() */
    static void DeleteAll();                         /* fn_1_E940 delete s_list.last() until empty */
    CObject();                                       /* fn_1_EA08 */
    virtual void draw(Mtx* mtx) {}                   /* fn_1_1AF8 weak (ball.o) */
    virtual void onFinish() {}                       /* fn_1_1AFC weak (ball.o); only called in mode 3 */
    int GetHandle();                                 /* fn_1_EB7C */
    static CObject* GetHandlePtr(int handle);
    /* fn_1_EC18: m539 scorespr execList (the delete-safe walk: the list moves to a local, each node is
     * re-inserted before fn runs). Takes CLinkList* (m539's: a typed list costs an extra register copy);
     * UpdateAll passes s_list.asList(). */
    static void execList(CLinkList* list, ExecFunc fn);

    static TLinkList<CObject> s_list;  /* bss A74 (DestructorChain A68) */
    static CHandleMan* s_handleMan;    /* bss A7C */

    int m_handle;                      /* 0x10 s_handleMan->insertHandle(this) */
};

} // namespace m532

#ifndef __MWERKS__
template <> m532::CObjectMan* CSingleton<m532::CObjectMan>::ms_pointer; /* defined in ball.cpp (bss_10) */
#endif

#endif
