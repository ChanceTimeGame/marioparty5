/* object_setup.cpp -- the REL entry: create the game master and set up the object manager (m539/m509's
 * ObjectSetup, only the size differs). __sinit: the 120/210/210 triple then the 300/60 pair (game_master.h). */
#include "REL/m532Dll/config.h"
#include "REL/m532Dll/game_master.h"

extern "C" void ObjectSetup(void)
{
    m532::CGameMaster* gm = new m532::CGameMaster;
    gm->setup(1, 0x2000);
}
