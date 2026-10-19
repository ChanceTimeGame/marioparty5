#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/assert.h"

s32 CSubThread::GetStartPriority()
{
    return OSGetThreadPriority(OSGetCurrentThread());
}

CSubThread::CSubThread(u32 stackSize) : m_th(ThreadMain, this, stackSize, GetStartPriority(), 1)
{
}

CSubThread::~CSubThread() {} /* m_th's dtor ends the thread (host: deletes the suspended coroutine) */

bool CSubThread::isTerminated()
{
    return ::OSIsThreadTerminated(m_th);
}

CThreadParam CSubThread::wakeupThread(CThreadParam param)
{
    if (::OSIsThreadTerminated(m_th)) {
        return m_param;
    }
    m_param = param;
    ::OSResumeThread(m_th);
    ::OSWaitSemaphore(m_sem);
    m_th.getStackRemain();
    ::OSCheckActiveThreads();
    return m_param;
}

/* (blank lines: the asserts below stay on their retail __LINE__) */






























/* called on the thread itself: hand `param` to the waker and wait for the next wakeupThread */
CThreadParam CSubThread::sleepThread(CThreadParam param)
{




    assert(::OSGetCurrentThread() == m_th);


    assert(!::OSIsThreadTerminated(m_th));
    m_param = param;
    ::OSSignalSemaphore(m_sem);
    ::OSSuspendThread(m_th);
    return m_param;
}

/* the thread entry (arg = the CSubThread): run the body with the first wakeup value, then release the waker */
void* CSubThread::ThreadMain(void* arg)
{
    CSubThread* self = (CSubThread*)arg;
    self->thread_exec(self->m_param);
    /* host: CThread's coroutine entry marks it terminated and switches back to the waker */
    ::OSSignalSemaphore(self->m_sem);
    return 0;
}
