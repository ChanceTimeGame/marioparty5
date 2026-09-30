#ifndef M536_TLINK_H
#define M536_TLINK_H

#include "REL/mgcpp/link.h"

template <class T> class TLinkList;

template <class T>
class TLinkItem : public CLinkNode {
public:
    TLinkItem() {}
    /* CLinkNode::insertBack takes a CLinkList*; a TLinkList is layout-identical (CLinkNode, no members) */
    /* retail passes the list straight through (m539 CScore ctor: asList() adds a register hop) */
    void insertBack(TLinkList<T>* l) { CLinkNode::insertBack((CLinkList*)l); }
    T* next() { return static_cast<T*>(m_next); }
};

template <class T>
class TLinkList : public CLinkNode {
public:
    typedef void (*ExecFunc)(T* item);

    T* begin() { return static_cast<T*>(CLinkNode::next()); }
    T* last() { return static_cast<T*>(CLinkNode::prev()); }
    CLinkNode* end() { return this; }
    CLinkList* asList() { return static_cast<CLinkList*>(static_cast<CLinkNode*>(this)); }

    /* outer: exec(list->begin(), list->end(), fn). Not inline (retail calls it; out-of-class template
     * definitions below are emitted weak at the end of each TU that uses them). */
    static void exec(TLinkList* list, ExecFunc fn);
    static void exec(T* it, CLinkNode* end, ExecFunc fn);
};

template <class T>
void TLinkList<T>::exec(TLinkList* list, ExecFunc fn)
{
    exec(list->begin(), list->end(), fn);
}

template <class T>
void TLinkList<T>::exec(T* it, CLinkNode* end, ExecFunc fn)
{
    while (it != end) {
        fn(it);
        it = it->next();
    }
}

#endif
