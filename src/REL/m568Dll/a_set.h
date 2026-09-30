/* a_set.h -- ASet<T> (m568's own revision of m539's set header): the one live list of T, reached through sm_ptr.
 * Retail asserts: a_set.h:29 (ctor, "sm_ptr == NULL") and a_set.h:58 (instance(), "sm_ptr != 0"); m539's
 * revision had them at 13/32. __LINE__ is an immediate and the strings are .data: keep both bodies on their
 * lines (pad or trim the comment lines above each when editing). m568: ASet<CPlayer> (game_master.o bss A0C),
 * ASet<CTube> (input.o 9F8), ASet<CObstacle> (input.o 9F4), all three owned by game_master's CObjSet.
 * Also the two pair walkers (weak templates, names ours): game_master's ForEachPair/ForEachCross (972C/97C0)
 * and player's ForEachPair with a functor (1198C). */
#ifndef M568_A_SET_H
#define M568_A_SET_H

#include "REL/mgcpp/assert.h"
#include "REL/mgcpp/tlink.h"

template <class T>
class ASet : public TLinkList<T> {
public:
    /* (layout: the ctor's assert must stay on line 29) */









    ASet()
    {
        assert(sm_ptr == NULL);
        sm_ptr = this;
    }
    ~ASet()
    {
        clear();
    }
    /* (layout: instance()'s assert must stay on line 58) */













    static ASet* instance()
    {
        assert(sm_ptr != 0);
        return sm_ptr;
    }

    /* one more inline level than the loop itself (m539's finding: it sets where CW's inline depth limit
     * outlines the MSL __vector_base accessors inside ~CObjSet, retail's 8380/837C). */
    void clear()
    {
        while (!this->isEmpty()) {
            delete this->last();
        }
    }

    /* (p->*f)() for every element, `next` read after the call (retail; no callback deletes its own element:
     * CPlayer::finish deletes TUBES during the player walk). The PTMF is taken by value (a stack temporary
     * copied from .data at the call); the end is read once. Host: T has no vptr, so T* and the CLinkNode*
     * sentinel agree. */
    void exec(void (T::*f)())
    {
        T* p = this->begin();
        CLinkNode* e = this->end();
        for (; p != e; p = p->next()) {
            (p->*f)();
        }
    }

    /* explicit specialisations at the end of input.cpp (CTube, CObstacle) and game_master.cpp (CPlayer): the
     * first TU in link order to instantiate them; host declarations in each element's header */
    static ASet* sm_ptr;
};

/* game_master 972C (weak, name ours): f(a, b) for every unordered pair; the outer walk stops at last() (the
 * list's +4), the inner one at the list; `next` read after the call. Masked-identical to m501's
 * execPlayerListReverse. */
template <class T>
void ForEachPair(TLinkList<T>* list, void (*f)(T* a, T* b))
{
    T* a = list->begin();
    CLinkNode* e = list->end();
    CLinkNode* l = e->prev(); /* retail reads the tail once, through the end node */
    for (; a != l; a = a->next()) {
        for (T* b = a->next(); b != e; b = b->next()) {
            f(a, b);
        }
    }
}

/* game_master 97C0 (weak, name ours): f(a, b) for every a in la and b in lb (both ends read once per loop) */
template <class T, class U>
void ForEachCross(TLinkList<T>* la, TLinkList<U>* lb, void (*f)(T* a, U* b))
{
    T* a = la->begin();
    CLinkNode* ea = la->end();
    for (; a != ea; a = a->next()) {
        U* b = lb->begin();
        CLinkNode* eb = lb->end();
        for (; b != eb; b = b->next()) {
            f(a, b);
        }
    }
}

#endif
