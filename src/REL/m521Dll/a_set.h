/* a_set.h -- ASet<T> (m521's revision): the one live list of T through sm_ptr. Asserts a_set.h:17 / :36
 * (keep both bodies on their lines: test/fixlines.py). m521: ASet<CPlayer> gamemaster .bss A70. ForEachPair: m568. */
#ifndef M521_A_SET_H
#define M521_A_SET_H

#include "REL/mgcpp/assert.h"
#include "REL/mgcpp/tlink.h"

template <class T>
class ASet : public TLinkList<T> {
public:
    /* (layout: the ctor's assert must stay on line 17) */


    ASet()
    {
        assert(sm_ptr == NULL);
        sm_ptr = this;
    }
    ~ASet()
    {
        clear();
    }

    /* (layout: instance()'s assert must stay on line 36) */




    static ASet* instance()
    {
        assert(sm_ptr != 0);
        return sm_ptr;
    }

    /* one more inline level than the loop itself (m539: decides where ~CObjSet outlines the MSL accessors) */
    void clear()
    {
        while (!this->isEmpty()) {
            delete this->last();
        }
    }

    /* (p->*f)() for every element, `next` read after the call (retail; no callback deletes its element) */
    void exec(void (T::*f)())
    {
        T* p = this->begin();
        CLinkNode* e = this->end();
        for (; p != e; p = p->next()) {
            (p->*f)();
        }
    }

    /* explicit specialisation at the end of gamemaster.cpp (.bss A70); host declaration in player.h */
    static ASet* sm_ptr;
};

/* gamemaster 134A8 (weak; = m568 972C): f(a, b) for every unordered pair */
template <class T>
void ForEachPair(TLinkList<T>* list, void (*f)(T* a, T* b))
{
    T* a = list->begin();
    CLinkNode* e = list->end();
    CLinkNode* l = e->prev();
    for (; a != l; a = a->next()) {
        for (T* b = a->next(); b != e; b = b->next()) {
            f(a, b);
        }
    }
}

#endif
