/* object_setup.cpp -- the REL entry: create the game master and set up the object manager.
 * EXACT: m539's / m532's ObjectSetup (only the class differs). object_setup.o carries the minigame.h triple
 * (.bss A18/A1C/A20, __sinit) through game_master.h. */
#include "REL/m568Dll/game_master.h"

extern "C" void ObjectSetup(void)
{
    m568::CGameMaster* gm = new m568::CGameMaster;
    gm->setup(1, 0x2000);
}
