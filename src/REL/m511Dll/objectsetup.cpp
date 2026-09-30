/* objectsetup.cpp -- the REL entry: create the game master and set up the object manager (m512's exactly). */
#include "REL/m511Dll/config.h"
#include "REL/m511Dll/gamemaster.h"

extern "C" void ObjectSetup(void)
{
    m511::CGameMaster* gm = new m511::CGameMaster;
    gm->setup(1, 0x2000);
}
