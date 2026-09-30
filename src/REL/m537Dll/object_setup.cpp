#include "REL/m537Dll/game_master.h"

extern "C" void ObjectSetup(void)
{
    m537::CGameMaster* gm = new m537::CGameMaster;
    gm->setup(1, 0x2000);
}
