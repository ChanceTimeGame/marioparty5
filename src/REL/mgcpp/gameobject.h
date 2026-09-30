/* gameobject.h -- CGameObject (gameobject.cpp): a polymorphic object on the global ObjectList, driven by
 * a per-mode exec bit: SetObjExecMode(m) sets bit (1<<m) in every object and calls on_new_mode(m); the
 * object clears its bit when it has finished that mode; CheckObjExec() is true when no bit is left.
 * GC layout: CLinkNode +0, vptr +8, m_execFlags +0xC; size 0x10. Three virtuals (the 6th word of
 * __vt__11CGameObject is .data padding). */
#ifndef MGCPP_GAMEOBJECT_H
#define MGCPP_GAMEOBJECT_H

#include "REL/mgcpp/link.h"

/* Base CLinkItem (link.h), the empty intermediate every retail list item has: the inlined CGameObject()
 * passes `this` through one more register before CLinkNode() (stage.o CStage ctor), ~CGameObject has one
 * more inlined null check than ~CLinkNode. Fork D used CLinkList for the same effect; both give identical
 * code in m501 and in D's camera/particle/stage (measured by FW1), CLinkItem is what fork A found. */
class CGameObject : public CLinkItem {
public:
    /* always inlined: CLinkNode(), vptr, m_execFlags = 0, insertBack(&ObjectList) */
    CGameObject()
    {
        m_execFlags = 0;
        insertBack(&ObjectList);
    }
#if defined(MGCPP_GAMEOBJECT_NO_VIRTUALS) && defined(__MWERKS__)
    /* m532/m517/m511's framework unit (with MGCPP_GAMEOBJECT_INLINE_UPDATE): neither virtual body nor the
     * vtable is there; the game units emit weak copies of all three (m532: ball.o). Declared out of line
     * in this TU only, so Close()'s delete and UpdateAll()'s call do not make CW emit them; the game units
     * define MGCPP_GAMEOBJECT_INLINE_UPDATE alone and see the inline bodies below (m532 W1). */
    virtual ~CGameObject();                  /* 0x08 */
    virtual void on_new_mode(int mode) = 0;  /* 0x0C */
    virtual void on_update();                /* 0x10 */
#else
    /* inline: retail derived dtors (camera/particle/stage) inline it; m501.cpp still emits the vtable
     * (key function on_update) and the out-of-line copy [fork D] */
    virtual ~CGameObject() {}                /* 0x08 */
    virtual void on_new_mode(int mode) = 0;  /* 0x0C */
#ifdef MGCPP_GAMEOBJECT_INLINE_UPDATE
    virtual void on_update() {}              /* 0x10 */
#else
    virtual void on_update();                /* 0x10 */
#endif
#endif

    static void SetObjExecMode(int mode);
    static bool CheckObjExec();
    static void UpdateAll();
    static void Close();
    static int GetUpdateMode();

    static CLinkList ObjectList;

    int m_execFlags; /* 0x0C (signed: CheckObjExec tests it with cmpwi) bit (1 << mode) while the object still runs that mode */
};

#endif
