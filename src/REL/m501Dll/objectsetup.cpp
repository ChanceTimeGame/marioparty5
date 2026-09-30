/* objectsetup.cpp -- the REL entry: create the game master and set up the object manager. */
#include "REL/m501Dll/gamemaster.h"

extern "C" void ObjectSetup(void)
{
    m501::CGameMaster* gm = new m501::CGameMaster;
    gm->setup(1, 0x2000);
}
