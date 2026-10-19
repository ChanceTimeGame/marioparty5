#ifndef MGCPP_LINK_H
#define MGCPP_LINK_H

#include "REL/mgcpp/game.h"

class CLinkList;

class CLinkNode {
public:
    CLinkNode();
    ~CLinkNode();
    /* retail symbol __ct__9CLinkNodeFR9CLinkNode: it unlinks `this` and self-links it; callers pass no
     * argument (map.txt) */
    void unlink();
    void insertFront(CLinkList* l);
    void insertBack(CLinkList* l);
    /* `this` is a list: moves all of its nodes to the tail of dst */
    void copyLink(CLinkList* dst);

    CLinkNode* next() { return m_next; }
    CLinkNode* prev() { return m_prev; }
    bool isEmpty() { return m_next == this && m_next == m_prev; }

    CLinkNode* m_next; /* 0x0 */
    CLinkNode* m_prev; /* 0x4 */
};

/* CLinkItem: the empty inline base between CLinkNode and retail's list-item classes (CGameObject, CPlayer,
 * CAisu, CAsiato; fork A). Constructing through it passes `this` through one more register before
 * __ct__9CLinkNodeFv, its implicit inline dtor adds one `this` test before ~CLinkNode, and CW writes an
 * out-of-line copy of that dtor after each derived ctor (aisu fn_1_7708, camera fn_1_9CE8, player
 * fn_1_B920 = __dt__9CLinkItemFv). No data, no virtuals: CLinkNode stays at offset 0 on every ABI. */
class CLinkItem : public CLinkNode {
public:
    CLinkItem() {}
};

/* comparator: returns true when a sorts before b. The retail symbol says void (map.txt) but the merge
 * tests the result. */
typedef bool (*CLinkCompareFunc)(CLinkNode* a, CLinkNode* b);
/* sortList's parameter type as retail declares it (symbol sortList__9CLinkListFPFP9CLinkNodeP9CLinkNode_v);
 * callers cast a CLinkCompareFunc to it and sortList casts it back */
typedef void (*CLinkSortFunc)(CLinkNode* a, CLinkNode* b);

class CLinkList : public CLinkNode {
public:
    CLinkNode* begin() { return m_next; }
    CLinkNode* last() { return m_prev; }
    /* typed first/last node: retail's extra register copy (`lwz rA,0(list); mr rB,rA; mr rC,rB`) wherever a
     * loop starts from a list's head/tail (gameobject.cpp; forks C/FW1). static_cast adjusts on every ABI. */
    template <class T> T* begin() { return static_cast<T*>(begin()); }
    template <class T> T* last() { return static_cast<T*>(last()); }
    CLinkNode* end() { return this; }
    void sortList(CLinkSortFunc cmp);
};

#endif
