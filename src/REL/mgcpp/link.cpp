/* link.cpp -- CLinkNode / CLinkList (intrusive circular doubly-linked lists; a list is its own sentinel)
 * and the list merge sort. */
#include "REL/mgcpp/link.h"

CLinkNode::CLinkNode()
{
    m_next = this;
    m_prev = this;
}

CLinkNode::~CLinkNode()
{
    m_next->m_prev = m_prev;
    m_prev->m_next = m_next;
}

/* takes the node out of its list and makes it a one-node ring (retail symbol __ct__9CLinkNodeFR9CLinkNode) */
void CLinkNode::unlink()
{
    m_next->m_prev = m_prev;
    m_prev->m_next = m_next;
    m_next = this;
    m_prev = this;
}

/* links this node at the head of l */
void CLinkNode::insertFront(CLinkList* l)
{
    CLinkNode* list = l;

    m_prev = list;
    m_next = list->m_next;
    list->m_next->m_prev = this;
    list->m_next = this;
}

/* links this node at the tail of l */
void CLinkNode::insertBack(CLinkList* l)
{
    CLinkNode* list = l;

    m_next = list;
    m_prev = list->m_prev;
    list->m_prev->m_next = this;
    list->m_prev = this;
}

/* `this` is a list: moves all of its nodes to the tail of dst and leaves this empty */
void CLinkNode::copyLink(CLinkList* dst)
{
    if (!isEmpty()) {
        CLinkNode* list = dst;
        CLinkNode* first = m_next;
        CLinkNode* last = m_prev;

        m_next = this;
        m_prev = this;
        first->m_prev = list->m_prev;
        last->m_next = list;
        list->m_prev->m_next = first;
        list->m_prev = last;
    }
}

static CLinkNode* MergeSort(CLinkCompareFunc cmp, CLinkNode* head);

/* stable merge sort of the list by cmp (true when a sorts before b) */
void CLinkList::sortList(CLinkSortFunc cmp)
{
    if (!isEmpty()) {
        CLinkNode* p;
        CLinkNode* prev;

        m_prev->m_next = NULL;
        p = MergeSort((CLinkCompareFunc)cmp, m_next);
        m_next = p;
        prev = this;
        while (p != NULL) {
            p->m_prev = prev;
            prev = p;
            p = p->m_next;
        }
        m_prev = prev;
        prev->m_next = this;
    }
}

static CLinkNode* SplitList(CLinkNode* head);
static CLinkNode* MergeList(CLinkCompareFunc cmp, CLinkNode* a, CLinkNode* b);

/* fn_1_19A4: sorts a NULL-terminated m_next chain (m_prev is not maintained); returns the new head */
static CLinkNode* MergeSort(CLinkCompareFunc cmp, CLinkNode* head)
{
    CLinkNode* b;
    CLinkNode* a;

    if (head == NULL) {
        return NULL;
    }
    if (head->m_next == NULL) {
        return head;
    }
    a = head;
    b = SplitList(a);
    a = MergeSort(cmp, a);
    b = MergeSort(cmp, b);
    return MergeList(cmp, a, b);
}

/* fn_1_204C: cuts the chain after its middle node; returns the second half */
static CLinkNode* SplitList(CLinkNode* head)
{
    CLinkNode* fast = head->m_next;

    if (fast != NULL) {
        fast = fast->m_next;
    }
    while (fast != NULL) {
        head = head->m_next;
        fast = fast->m_next;
        if (fast != NULL) {
            fast = fast->m_next;
        }
    }
    fast = head->m_next;
    head->m_next = NULL;
    return fast;
}

/* fn_1_20A0: merges two sorted chains, taking from a while cmp(a, b) */
static CLinkNode* MergeList(CLinkCompareFunc cmp, CLinkNode* a, CLinkNode* b)
{
    /* a dummy head: only its m_next (offset 0, as in CLinkNode on every target) is used, no ctor */
    struct {
        CLinkNode* m_next;
        CLinkNode* m_prev;
    } head;
    CLinkNode* tail = reinterpret_cast<CLinkNode*>(&head);

    while (a != NULL && b != NULL) {
        if (cmp(a, b)) {
            tail->m_next = a;
            tail = a;
            a = a->m_next;
        } else {
            tail->m_next = b;
            tail = b;
            b = b->m_next;
        }
    }
    if (a == NULL) {
        tail->m_next = b;
    } else {
        tail->m_next = a;
    }
    return head.m_next;
}
