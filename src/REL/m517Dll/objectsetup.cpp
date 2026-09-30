#include "REL/m517Dll/config.h"
#include "REL/m517Dll/gamemaster.h"

extern "C" void ObjectSetup(void)
{
    m517::CGameMaster* gm = new m517::CGameMaster;
    gm->setup(1, 0x2000);
}
