/* man_object.cpp -- m532::CObjectMan / CObject (man_object.h). Retail order: CObjectMan ctor,
 * [~CSingleton<CObjectMan>], dtor, on_new_mode, on_update; CObject::UpdateAll, Update, update, HookFunc,
 * FinishAll, Finish, DeleteAll, ctor, [~TLinkItem<CObject>], dtor, GetHandle, GetHandlePtr,
 * [TLinkList<CObject>::exec outer], execList, [~TLinkList<CObject>], [exec inner], __sinit (s_list).
 * EXACT (m539 scorespr shapes, adapted by name): ~CObjectMan (F150), on_update (F238), UpdateAll (F55C),
 * execList (F914), the TLinkItem / TLinkList dtors (F3B4 / FA04). The rest drafted whole from the sheet
 * (ball_referee_unk.md §3.3). No minigame.h, no param.h (no triple, no pair in man_object.o). */
#include "REL/m532Dll/man_object.h"

namespace m532 {

TLinkList<CObject> CObject::s_list;
CHandleMan* CObject::s_handleMan;

CObjectMan::CObjectMan(CHandleMan* handleMan) : m_handleMan(handleMan)
{
    CObject::s_handleMan = m_handleMan;
}

CObjectMan::~CObjectMan()
{
    CObject::DeleteAll();
}

/* retail: the bit is cleared first, then a compare tree with EMPTY cases 0 and 5 (m501 NOTES: CW adds a `beq`
 * for them -- the fork records the residue); mode 3 finishes every object and clears the bit again */
void CObjectMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
        break;
    case 3:
        CObject::FinishAll();
        m_execFlags &= ~(1 << mode);
        break;
    case 5:
        break;
    }
}

void CObjectMan::on_update()
{
    CObject::UpdateAll();
}

void CObject::UpdateAll()
{
    execList(s_list.asList(), Update);
}

void CObject::Update(CObject* o)
{
    o->update();
}

void CObject::update() {}

void CObject::HookFunc(HU3DMODEL* model, Mtx* mtx)
{
    ((CObject*)model->hookData)->draw(mtx);
}

void CObject::FinishAll()
{
    TLinkList<CObject>::exec(&s_list, Finish);
}

void CObject::Finish(CObject* o)
{
    o->onFinish();
}

void CObject::DeleteAll()
{
    while (!s_list.isEmpty()) {
        delete s_list.last();
    }
}

CObject::CObject() : CModel(HookFunc)
{
    m_handle = s_handleMan->insertHandle(this);
    insertBack(&s_list);
    setHookData(this);
}

CObject::~CObject()
{
    s_handleMan->removeHandle(m_handle);
}

int CObject::GetHandle()
{
    return m_handle;
}

CObject* CObject::GetHandlePtr(int handle)
{
    return (CObject*)s_handleMan->getHandlePtr(handle);
}

void CObject::execList(CLinkList* list, ExecFunc fn)
{
    if (!list->isEmpty()) {
        TLinkList<CObject> tmp;
        list->copyLink(tmp.asList());
        while (!tmp.isEmpty()) {
            CObject* o = tmp.begin();
            o->unlink();
            o->CLinkNode::insertBack(list);
            fn(o);
        }
    }
}

} // namespace m532
