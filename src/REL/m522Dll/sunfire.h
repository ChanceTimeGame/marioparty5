#ifndef M522_SUNFIRE_H
#define M522_SUNFIRE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/handle.h"
#include "REL/mgcpp/tlink.h"

namespace m522 {

class CSunFireMan : public CGameObject, public CSingleton<CSunFireMan> {
public:
    CSunFireMan(CHandleMan* handleMan); /* fn_1_DEA0 */
    virtual ~CSunFireMan();             /* fn_1_E04C CSunFireObj::DeleteAll (= m532 E6C4) */
    /* fn_1_E11C: HuSprTexLoad(GetInstance()->m_anim[anim], 0, texMap, s, t, f) (fire DrawObj) */
    static void LoadTex(int anim, int texMap, GXTexWrapMode s, GXTexWrapMode t, GXTexFilter f);
    virtual void on_new_mode(int mode); /* fn_1_E1D4 mode 3: CSunFireObj::FinishAll (= m532 E794) */
    virtual void on_update();           /* fn_1_E250 CSunFireObj::UpdateAll */

    ANIMDATA* m_anim[2];                /* 0x10 0x500005 (fire01 sheet), 0x500006 (prominence sheet) */
    CHandleMan* m_handleMan;            /* 0x18 the game master's m_handleMan; also CSunFireObj::s_handleMan */
};

class CSunFireObj : public TLinkItem<CSunFireObj>, public CModel {
public:
    typedef void (*ExecFunc)(CSunFireObj* o);

    /* the vtable slot order is DECLARATION order ({~, update, draw, onFinish}); definition order is retail's */
    virtual ~CSunFireObj();                           /* fn_1_E534 key function: the vtable is sunfire.o's */
    static void UpdateAll();                          /* fn_1_E270 execList(&s_list, Update) */
    static void Update(CSunFireObj* o);               /* fn_1_E2A0 o->update() */
    virtual void update();                            /* fn_1_E2D4 empty */
    static void HookFunc(HU3DMODEL* model, Mtx* mtx); /* fn_1_E2D8 ((CSunFireObj*)model->hookData)->draw(mtx) */
    virtual void draw(Mtx* mtx);                      /* fn_1_E31C empty (out of line) */
    static void FinishAll();                          /* fn_1_E320 TLinkList exec (plain walk) of Finish */
    static void Finish(CSunFireObj* o);               /* fn_1_E350 o->onFinish() */
    static void DeleteAll();                          /* fn_1_E384 delete s_list.last() until empty */
    CSunFireObj();                                    /* fn_1_E44C */
    virtual void onFinish() {}                        /* fn_1_26A4 weak (fire.o); mode 3 only */
    int GetHandle();                                  /* fn_1_E5C0 (bubble Spawn) */
    static CSunFireObj* GetHandlePtr(int handle);     /* fn_1_E5C8 0 for a stale handle (bubble, player) */
    /* fn_1_E65C: the delete-safe walk (m532 EC18): the list moves to a local, each node is re-inserted before fn */
    static void execList(CLinkList* list, ExecFunc fn);

    static TLinkList<CSunFireObj> s_list; /* bss A3C (DestructorChain A30) */
    static CHandleMan* s_handleMan;       /* bss A44 */

    int m_handle;                         /* 0x10 s_handleMan->insertHandle(this) */
};

} // namespace m522

#ifndef __MWERKS__
template <> m522::CSunFireMan* CSingleton<m522::CSunFireMan>::ms_pointer; /* defined in fire.cpp (bss 0x14) */
#endif

#endif
