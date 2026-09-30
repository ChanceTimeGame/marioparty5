#include "REL/mgcpp/gameobject.h"

CLinkList CGameObject::ObjectList;
static int s_updateMode; /* lbl_1_bss_14 */

void CGameObject::SetObjExecMode(int mode)
{
    CLinkNode* p = ObjectList.begin<CGameObject>();
    CLinkNode* end = ObjectList.end();

    s_updateMode = mode;
    for (; p != end; p = p->next()) {
        static_cast<CGameObject*>(p)->m_execFlags |= 1 << mode;
        static_cast<CGameObject*>(p)->on_new_mode(mode);
    }
}

/* true when no object still runs the current mode */
bool CGameObject::CheckObjExec()
{
    CLinkNode* p = ObjectList.begin<CGameObject>();
    CLinkNode* end = ObjectList.end();

    for (; p != end; p = p->next()) {
        int mode = s_updateMode;
        if (static_cast<CGameObject*>(p)->m_execFlags & (1 << mode)) {
            return false;
        }
    }
    return true;
}

void CGameObject::UpdateAll()
{
    CLinkNode* p = ObjectList.begin<CGameObject>();
    CLinkNode* end = ObjectList.end();

    for (; p != end; p = p->next()) {
        static_cast<CGameObject*>(p)->on_update();
    }
}

#ifndef MGCPP_GAMEOBJECT_INLINE_UPDATE
void CGameObject::on_update() {}
#endif

/* deletes every object, last first */
void CGameObject::Close()
{
    while (!ObjectList.isEmpty()) {
        delete ObjectList.last<CGameObject>();
    }
}

/* ~CGameObject is inline in gameobject.h; retail emits it here (0x23AC) */

int CGameObject::GetUpdateMode()
{
    return s_updateMode;
}
