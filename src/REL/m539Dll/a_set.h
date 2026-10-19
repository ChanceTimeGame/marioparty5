/* a_set.h -- ASet<T> (m539's own set header): the one live list of T, reached through sm_ptr. */
#ifndef M539_A_SET_H
#define M539_A_SET_H

#include "REL/mgcpp/assert.h"
#include "REL/mgcpp/tlink.h"

template <class T>
class ASet : public TLinkList<T> {
public:
    ASet()
    {
        assert(sm_ptr == NULL);
        sm_ptr = this;
    }
    ~ASet()
    {
        clear();
    }
    /* the asserts sit on the retail lines a_set.h:13 (ctor) and :32 (instance): __LINE__ is an immediate
     * and the strings are .data. Keep this layout (pad or trim these comment lines when editing above). */








    static ASet* instance()
    {
        assert(sm_ptr != 0);
        return sm_ptr;
    }

    /* one more inline level than the loop itself: in ~CObjSet (fn_1_83FC) CW then reaches its inline depth
     * limit inside CPlayer's vector<s16> dtor and calls the weak __vector_base accessors out of line, as retail
     * does, while the out-of-line ~ASet<CPlayer> (88CC) still inlines them (tested; a second level here
     * outlines the whole ~ASet<CPlayer> from ~CObjSet). Retail calls TWO accessors there: 86A8 (the capacity
     * argument, evaluated first) and 86A4 (alloc()). The capacity one comes out only when MSL's POD
     * ~__vector_base reads the capacity through a non-leaf accessor (`cap()`); with `cap_.first()` (a leaf) CW
     * inlines it at any depth, so no spelling here can produce 86A8 (fork F4 OUT.md: the MSL change). */
    void clear()
    {
        while (!this->isEmpty()) {
            delete this->last();
        }
    }

    /* (p->*f)() for every element, `next` read after the call (retail; no callback deletes its element).
     * The PTMF is taken by value (a stack temporary copied from .data at the call). The end is read once,
     * before the loop (retail `mr rE,set; mr rF,rE`). Callers take the set into a local first: retail
     * evaluates instance() (the assert) before the PTMF copy. game_master's "stack-spilled" walks are this
     * same loop after the registers r17..r31 run out (on_update's second walk, thread_exec). Host: T has no
     * vptr, so T* and the CLinkNode* sentinel agree. */
    void exec(void (T::*f)())
    {
        T* p = this->begin();
        CLinkNode* e = this->end();
        for (; p != e; p = p->next()) {
            (p->*f)();
        }
    }

    /* explicit specialisations at the end of game_master.cpp (the first TU in link order to instantiate them);
     * host declarations in score.h / player.h */
    static ASet* sm_ptr;
};

#endif
