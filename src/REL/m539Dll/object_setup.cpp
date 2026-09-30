/* object_setup.cpp -- the REL entry: create the game master and set up the object manager (as m536). */
#include "REL/m539Dll/game_master.h"

extern "C" void ObjectSetup(void)
{
    m539::CGameMaster* gm = new m539::CGameMaster;
    gm->setup(1, 0x2000);
}
