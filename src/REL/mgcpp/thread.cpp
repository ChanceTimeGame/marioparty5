#include "REL/mgcpp/thread.h"
#include "REL/mgcpp/new.h"
#include "REL/mgcpp/assert.h"

static bool s_debug; /* lbl_1_bss_24: stack fill + "delete CThread@" report; never set on retail */

#define STACK_MAGIC 0xDEADBABE
#define STACK_GUARD_WORDS 8

/* the stack is new u32[stackSize / 4] from the overlay heap (host: libco allocates its own) */
CThread::CThread(CThreadFunc func, void* arg, u32 stackSize, s32 prio, u16 attr)
{
    u32 words = stackSize / sizeof(u32);
    u32* stack = new u32[words];
    m_stack = stack;
    createThread(func, arg, stack, words, prio, attr);
}

CThread::CThread(CThreadFunc func, void* arg, u32* stack, u32 stackSize, s32 prio, u16 attr)
{
    m_stack = NULL;
    u32 words = stackSize / sizeof(u32);
    createThread(func, arg, stack, words, prio, attr);
}


/* created suspended; retail attr is OS_THREAD_ATTR_DETACH (1) from CSubThread */
void CThread::createThread(CThreadFunc func, void* arg, u32* stack, u32 words, s32 priority, u16 attr)
{
























    assert(priority >= OS_PRIORITY_MIN && priority <= OS_PRIORITY_MAX);
    initStack(stack, words);
    checkStackOverflow(stack, 0);
    bool created = ::OSCreateThread(&m_thread, func, arg, stack + words, words * sizeof(u32), priority, attr);
    if (!created) {









        OSHalt("OSCreateThread() failed.");
    }
}

CThread::~CThread()
{
    if (!::OSIsThreadTerminated(&m_thread)) {
        ::OSCancelThread(&m_thread);
    }
    if (s_debug) {
        u32 total = (u32)m_thread.stackBase - (u32)m_thread.stackEnd;
        u32 remain = getStackRemain();
        printf("delete CThread@%p\nstack remain/total = 0x%08x/0x%08x (%f%%)\n", this, remain, total,
               100.0 * remain / total);
    }
    delete[] m_stack;
}

/* bytes of the stack never written (still STACK_MAGIC); halts if the guard was overwritten */
u32 CThread::getStackRemain()
{
    u32* end = m_thread.stackEnd;
    if (checkStackOverflow(end, 1)) {
        OSHalt("stack overflow\n");
    }
    u32* p = end;
    u32* base = (u32*)m_thread.stackBase;
    for (; p < base; p++) {
        if (*p != STACK_MAGIC) {
            break;
        }
    }
    return (u32)p - (u32)end;
}

/* mode 0: write the guard words; mode 1: 1 if any guard word changed. Other modes: 0. */
int CThread::checkStackOverflow(u32* p, int mode)
{
    u32* end = p + STACK_GUARD_WORDS;
    switch (mode) {
    case 0:
        while (p != end) {
            *p++ = STACK_MAGIC;
        }
        break;
    case 1:
        while (p != end) {
            if (*p++ != STACK_MAGIC) {
                return 1;
            }
        }
        break;
    }
    return 0;
}

/* debug only: fill the whole stack so getStackRemain can measure the high-water mark */
void CThread::initStack(u32* p, u32 words)
{
    if (s_debug) {
        u32* end = p + words;
        while (p != end) {
            *p++ = STACK_MAGIC;
        }
    }
}

