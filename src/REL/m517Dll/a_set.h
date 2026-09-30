/* a_set.h -- ASet<T> (m513's revision, asserts a_set.h:21 ctor "sm_ptr == NULL" / :46 instance() "sm_ptr != 0"):
 * the one live list of T through sm_ptr. __LINE__ is an immediate and the strings are .data: keep both bodies on
 * their lines. m517: ASet<CBall> effect.o .bss 0, ASet<CPlayer> input.o A08, ASet<CChoro> gamemaster.o A1C (all
 * owned by gamemaster's CObjSet). ForEachPair / ForEachCross: m568's weak pair walkers (gamemaster BCD8 / BBA0 /
 * BC3C, d=0). EXACT (m513 / m568). */
#ifndef M517_A_SET_H
#define M517_A_SET_H

#include "REL/mgcpp/assert.h"
#include "REL/mgcpp/tlink.h"

template <class T>
class ASet : public TLinkList<T> {
public:
    /* (layout: the ctor's assert must stay on line 21) */



    ASet()
    {
        assert(sm_ptr == NULL);
        sm_ptr = this;
    }
    ~ASet()
    {
        clear();
    }
    /* (layout: instance()'s assert must stay on line 46) */









    static ASet* instance()
    {
        assert(sm_ptr != 0);
        return sm_ptr;
    }

    /* one more inline level than the loop itself (m539's finding: it sets where CW's inline depth limit
     * outlines the MSL __vector_base accessors inside ~CObjSet, retail's BB70/BB6C). */
    void clear()
    {
        while (!this->isEmpty()) {
            delete this->last();
        }
    }

    /* (p->*f)() for every element, `next` read after the call (retail; no callback deletes its own element).
     * The PTMF is taken by value (a stack temporary copied from .data at the call); the end is read once.
     * Host: T has no vptr, so T* and the CLinkNode* sentinel agree. */
    void exec(void (T::*f)())
    {
        T* p = this->begin();
        CLinkNode* e = this->end();
        for (; p != e; p = p->next()) {
            (p->*f)();
        }
    }

    /* explicit specialisations at the end of effect.cpp (CBall), input.cpp (CPlayer), gamemaster.cpp (CChoro):
     * the TU whose .bss retail gives them; host declarations in each element's header */
    static ASet* sm_ptr;
};

/* gamemaster BCD8 (weak; = m568 972C / m521 134A8): f(a, b) for every unordered pair */
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

/* gamemaster BBA0 / BC3C (weak; = m568 97C0): f(a, b) for every a in la and b in lb */
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
