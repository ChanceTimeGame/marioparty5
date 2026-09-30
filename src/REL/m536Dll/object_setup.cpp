/* object_setup.cpp -- the REL entry: create the game master and set up the object manager. */
#include "REL/m536Dll/game_master.h"

extern "C" void ObjectSetup(void)
{
    m536::CGameMaster* gm = new m536::CGameMaster;
    gm->setup(1, 0x2000);
}
