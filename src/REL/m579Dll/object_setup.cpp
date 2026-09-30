#include "REL/m579Dll/game_master.h"

extern "C" void ObjectSetup(void)
{
    m579::CGameMaster* gm = new m579::CGameMaster;
    gm->setup(1, 0x2000);
}
