/* objectsetup.cpp -- the REL entry: create the CFlow (whose inline ctors -- CGameMaster(), CFlow() -- expand here,
 * with CGameMaster's vtable and its inline dtor emitted in this unit) and set up the object manager
 * (50 objects, prio 0x2000). Written whole (skeleton). */
#include "REL/m531Dll/flow.h"

extern "C" void ObjectSetup(void)
{
    m531::CFlow* gm = new m531::CFlow;
    gm->setup(0x32, 0x2000);
}
