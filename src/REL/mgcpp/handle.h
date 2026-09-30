#ifndef MGCPP_HANDLE_H
#define MGCPP_HANDLE_H

#include "REL/mgcpp/game.h"

class CHandleMan {
public:
    enum { MAXCOUNT = 0x1000 };
    struct Node {
        Node* next;  /* 0x0 */
        Node* prev;  /* 0x4 */
        void* ptr;   /* 0x8 */
#ifdef __MWERKS__
        /* retail touches the low 12 bits as a halfword (lhz/sth +0xE) and the whole word as the handle */
        union {
            struct {
                u32 index : 20;
                u32 serial : 12;
            } bits;
            u32 handle;
        };           /* 0xC */
#else
        u32 handle;  /* index << 12 | serial -- shifts only on the host */
#endif
    };

    CHandleMan(unsigned int n);   /* __ct__10CHandleManFUi */
    ~CHandleMan();
    int insertHandle(void* p);
    void* removeHandle(int h);
    void* getHandlePtr(int h);
    int getHandleNum();
    int getEndHandleNum();
    int getBeginHandleNum();

    Node* m_nodes; /* 0x0 node[0] = free-ring sentinel */
    Node* m_used;  /* 0x4 = &m_nodes[n], used-ring sentinel */
    u32 m_count;   /* 0x8 n */
};

#endif
