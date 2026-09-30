/* a_set.h -- ASet<T> (m513's own revision, the third after m539 / m568): the one live list of T, reached
 * through sm_ptr. Retail asserts: a_set.h:21 (ctor, "sm_ptr == NULL") and a_set.h:46 (instance(),
 * "sm_ptr != 0"). __LINE__ is an immediate and the strings are .data: keep both bodies on their lines (pad
 * or trim the comment lines above each; test/fixlines.py). m513: ASet<CPlayer> A10, ASet<CLeaf> 9F8 (leaf.o),
 * ASet<CHeiho> A14, ASet<CKuribo> A0C (gamemaster.o), all four owned by gamemaster's CObjSet. */
#ifndef M513_A_SET_H
#define M513_A_SET_H

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

    /* explicit specialisations at the end of leaf.cpp (CLeaf) and gamemaster.cpp (CKuribo, CPlayer, CHeiho):
     * the TU whose .bss retail gives them; host declarations in each element's header */
    static ASet* sm_ptr;
};

#endif
