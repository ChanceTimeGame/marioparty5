/* objectsetup.cpp -- the REL entry points and ObjectSetup. m509 (the older framework) keeps _prolog/_epilog
 * here, not in the framework's new.cpp (MGCPP_V0_NO_PROLOG in m509.cpp); _prolog returns void. Retail order:
 * _prolog, _epilog, ObjectSetup, __sinit (the minigame.h triple, through gamemaster.h). */
#include "REL/m509Dll/gamemaster.h"

#ifdef __MWERKS__
/* The GameCube loader's entry points; the port calls ObjectSetup directly and has no _ctors/_dtors. */
extern "C" {
typedef void (*VoidFunc)(void);
extern const VoidFunc _ctors[];
extern const VoidFunc _dtors[];
void ObjectSetup(void);

void _prolog(void)
{
    const VoidFunc* ctors = _ctors;
    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
    ObjectSetup();
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

extern "C" void ObjectSetup(void)
{
    m509::CGameMaster* gm = new m509::CGameMaster;
    gm->setup(1, 0x2000);
}
