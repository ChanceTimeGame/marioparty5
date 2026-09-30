#ifndef MGCPP_THREAD_H
#define MGCPP_THREAD_H

#include "REL/mgcpp/game.h"

typedef void* (*CThreadFunc)(void* arg);

class CThread {
public:
    CThread(CThreadFunc func, void* arg, u32 stackSize, s32 prio, u16 attr);
    CThread(CThreadFunc func, void* arg, u32* stack, u32 stackSize, s32 prio, u16 attr);
    void createThread(CThreadFunc func, void* arg, u32* stack, u32 words, s32 prio, u16 attr);
    ~CThread();
    u32 getStackRemain();
    static int checkStackOverflow(u32* p, int mode);
    static void initStack(u32* p, u32 words);

    /* the subthread.cpp asserts compare ::OSGetCurrentThread() with m_th and pass m_th to
     * ::OSIsThreadTerminated, so the thread converts to OSThread* */
    operator OSThread*() { return &m_thread; }

    OSThread m_thread; /* 0x000 */
    u32* m_stack;      /* 0x318 owned stack, 0 when the caller supplied it */
};

#endif
