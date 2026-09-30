/* objectsetup.cpp -- the REL entry: create the game master and set up the object manager (as m536). */
#include "REL/m512Dll/gamemaster.h"

extern "C" void ObjectSetup(void)
{
    m512::CGameMaster* gm = new m512::CGameMaster;
    gm->setup(1, 0x2000);
}
