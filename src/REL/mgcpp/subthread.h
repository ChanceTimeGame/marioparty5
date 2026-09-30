/* subthread.h -- CSubThread (subthread.cpp): a coroutine-style worker. wakeupThread(v) runs the thread
 * until it calls sleepThread(v') (or returns); each side gets the other's value through m_param.
 * The thread body is the pure virtual thread_exec(int), called by ThreadMain with m_param.
 * GC: vptr +0, pad +4, CThread m_th +8 (0x320), OSSemaphore m_sem +0x328, m_param +0x334; size 0x338. */
#ifndef MGCPP_SUBTHREAD_H
#define MGCPP_SUBTHREAD_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/thread.h"

/* An OSSemaphore with an inline init and an OSSemaphore* conversion: retail passes &m_sem to the
 * Wait/Signal calls through a register copy, the mark of an inlined conversion (like CThread's
 * operator OSThread*), and initialises it as a member after m_th. 0xC bytes, no dtor. Name is ours. */
class CSemaphore {
public:
    CSemaphore() { OSInitSemaphore(&m_sem, 0); }
    operator OSSemaphore*() { return &m_sem; }

    OSSemaphore m_sem;
};

/* The value wakeupThread/sleepThread hand across (m_param). Retail passes ints and, in m539's CInputCom,
 * a pointer through the same int: the host widens it so a pointer survives 64 bits. `int` on CW, so every
 * object and mangled name is unchanged. */
typedef int CThreadParam;

class CSubThread {
public:
    virtual ~CSubThread();                 /* 0x08 key function */
    /* 0x0C. ThreadMain passes m_param (r4), so the slot takes an int; CGameMaster's override is named
     * thread_exec__Q24m50111CGameMasterFv in symbols.txt (map.gamemaster.txt). */
    virtual void thread_exec(CThreadParam param) = 0;

    static s32 GetStartPriority();
    CSubThread(u32 stackSize);
    bool isTerminated();
    CThreadParam wakeupThread(CThreadParam param);
    CThreadParam sleepThread(CThreadParam param);
    static void* ThreadMain(void* arg);

    CThread m_th;      /* 0x008 */
    CSemaphore m_sem;  /* 0x328 */
    CThreadParam m_param; /* 0x334 */
};

#endif
