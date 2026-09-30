/* handle.cpp -- CHandleMan: a fixed pool of n handles. A handle is (index << 12) | serial; the serial is
 * bumped on every insert so a stale handle no longer matches its node. node[0] is the free-ring sentinel
 * (nodes 1..n-1 start on it), node[n] the used-ring sentinel. The assert must stay on line 68. */
#include "REL/mgcpp/handle.h"
#include "REL/mgcpp/new.h"
#include "REL/mgcpp/assert.h"

/* A handle argument is copied into this union (retail decodes its index from the stack copy). */
union Handle {
    u32 handle;
    struct {
        u32 index : 20;
        u32 serial : 12;
    } bits;
};

#define HANDLE_ARG_INDEX(u) ((u).bits.index)





































CHandleMan::CHandleMan(unsigned int n)
{
    u32 i;

    assert(n <= MAXCOUNT);
    m_count = n;
    m_nodes = new Node[n + 1];
    m_used = &m_nodes[n];
    m_used->next = m_used;
    m_used->prev = m_used;
    for (i = 1; i < n; i++) {
        m_nodes[i].next = m_nodes + i + 1;
        m_nodes[i].prev = m_nodes + i - 1;
        m_nodes[i].ptr = 0;
        m_nodes[i].bits.index = i;
        m_nodes[i].bits.serial = 0;
    }
    m_nodes[1].prev = &m_nodes[0];
    m_nodes[n - 1].next = &m_nodes[0];
    m_nodes[0].next = &m_nodes[1];
    m_nodes[0].prev = m_nodes + n - 1;
}

CHandleMan::~CHandleMan()
{
    delete[] m_nodes;
}

/* takes a free node, links it at the front of the used ring; 0 when the pool is full */
int CHandleMan::insertHandle(void* p)
{
    Node* node = m_nodes->next;

    if (node == m_nodes) {
        return 0;
    }
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = m_used->next;
    node->prev = m_used;
    m_used->next->prev = node;
    m_used->next = node;
    node->ptr = p;
    node->bits.serial++;
    return node->handle;
}

/* releases h (back of the free ring); returns its pointer, or 0 when h is 0, out of range or stale */
void* CHandleMan::removeHandle(int h)
{
    Handle u;
    Node* node;
    void* p;

    u.handle = h;
    if ((u32)h == 0) {
        return 0;
    }
    if (HANDLE_ARG_INDEX(u) >= m_count) {
        return 0;
    }
    node = &m_nodes[HANDLE_ARG_INDEX(u)];
    if (node->handle != (u32)h) {
        return 0;
    }
    p = node->ptr;
    node->ptr = 0;
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = m_nodes;
    node->prev = m_nodes->prev;
    m_nodes->prev->next = node;
    m_nodes->prev = node;
    return p;
}

void* CHandleMan::getHandlePtr(int h)
{
    Handle u;
    Node* node;

    u.handle = h;
    if ((u32)h == 0) {
        return 0;
    }
    if (HANDLE_ARG_INDEX(u) >= m_count) {
        return 0;
    }
    node = &m_nodes[HANDLE_ARG_INDEX(u)];
    if (node->handle != (u32)h) {
        return 0;
    }
    return node->ptr;
}

/* retail bug (unreferenced): walks from (Node*)this, i.e. the free ring, which never comes back to `this` */
int CHandleMan::getHandleNum()
{
    int count = 0;
    Node* p = ((Node*)this)->next;

    while (p != (Node*)this) {
        p = p->next;
        count++;
    }
    return count;
}

/* number of used handles */
int CHandleMan::getEndHandleNum()
{
    Node* p;
    int count;
    Node* end = m_used;

    count = 0;
    p = end->next;

    while (p != end) {
        p = p->next;
        count++;
    }
    return count;
}

/* number of free nodes */
int CHandleMan::getBeginHandleNum()
{
    Node* p;
    int count;
    Node* end = m_nodes;

    count = 0;
    p = end->next;

    while (p != end) {
        p = p->next;
        count++;
    }
    return count;
}
