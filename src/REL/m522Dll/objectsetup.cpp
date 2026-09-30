#include "REL/m522Dll/gamemaster.h"

extern "C" void actorSetup__13CMinigameCoreFii(CMinigameCore* self);

extern "C" void ObjectSetup(void)
{
    m522::CGameMaster* gm = new m522::CGameMaster;
    actorSetup__13CMinigameCoreFii(gm);
}
