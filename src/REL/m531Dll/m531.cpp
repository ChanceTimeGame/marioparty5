/* m531.cpp -- the minigame framework unit of m531dll: the shared framework (src/REL/mgcpp) as one translation
 * unit, in retail order. m531's list (plan Phase 4 framework survey) is the smallest: new, assert, camera,
 * minigame, om, timer -- no list/game-object/model/random/thread code in this unit. */
#include "REL/mgcpp/new.cpp"
#include "REL/mgcpp/assert.cpp"
#include "REL/mgcpp/camera.cpp"
#include "REL/mgcpp/minigame.cpp"
#include "REL/mgcpp/om.cpp"
#include "REL/mgcpp/timer.cpp"

/* The CMinigameCore singleton pointer: retail's weak template static, at the end of the TU's .bss. */
template <> CMinigameCore* CSingleton<CMinigameCore>::ms_pointer = 0;
