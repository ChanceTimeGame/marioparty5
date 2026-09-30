/* objectsetup.cpp -- the REL entry: create the game master and set up the object manager (= m579 / m537 ObjectSetup
 * with the 0x3B0 master; `setup(1, 0x2000)`, no actorSetup). objectsetup.o carries the minigame.h triple (.bss
 * A88..A90, __sinit) through gamemaster.h, and no .data. EXACT. */
#include "REL/m521Dll/gamemaster.h"

extern "C" void ObjectSetup(void)
{
    m521::CGameMaster* gm = new m521::CGameMaster;
    gm->setup(1, 0x2000);
}
