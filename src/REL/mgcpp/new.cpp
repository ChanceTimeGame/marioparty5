/* new.cpp -- global operator new/delete (overlay heap, HU_MEMNUM_OVL) and the REL entry points.
 * The assert must stay on line 23 (its __LINE__ is part of the code). */
#include "REL/mgcpp/new.h"
#include "REL/mgcpp/assert.h"


/* Both allocators assert on line 23: new[] forwards to new, which CW inlines. */











/* operator new: never returns NULL (asserts new.cpp:23) */
void* operator new(size_t size)
{
    void* ptr = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    assert(ptr != NULL);
    return ptr;
}

void* operator new[](size_t size)
{
    return operator new(size);
}

void operator delete(void* p)
{
    if (p) {
        HuMemDirectFree(p);
    }
}

void operator delete[](void* p)
{
    operator delete(p);
}
/* knob MGCPP_V0_NO_PROLOG: m509 (older framework) has _prolog/_epilog in its objectsetup.cpp, not here */
#if defined(__MWERKS__) && !defined(MGCPP_V0_NO_PROLOG)
/* The GameCube loader's entry points; the port calls ObjectSetup directly and has no _ctors/_dtors. */
extern "C" {
typedef void (*VoidFunc)(void);
extern const VoidFunc _ctors[];
extern const VoidFunc _dtors[];
void ObjectSetup(void);

int _prolog(void)
{
    const VoidFunc* ctors = _ctors;
    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
    ObjectSetup();
    return 0;
}

void _epilog(void)
{
    const VoidFunc* dtors = _dtors;
    while (*dtors != 0) {
        (**dtors)();
        dtors++;
    }
}
}
#endif
