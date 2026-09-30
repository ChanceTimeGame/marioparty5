#include "REL/m513Dll/gamemaster.h"

extern "C" void ObjectSetup(void)
{
    m513::CGameMaster* gm = new m513::CGameMaster;
    gm->setup(1, 0x2000);
}
