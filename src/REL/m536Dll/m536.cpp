/* m536.cpp -- the minigame framework unit of m536dll: the shared framework (src/REL/mgcpp) as one
 * translation unit, in retail order. m536's list (plan Phase 4 framework survey): no handle.cpp; random.cpp
 * between om.cpp and sphere.cpp, so its CMT19937 calls inline and __sinit seeds CRandom::randInstance. */
#include "REL/mgcpp/new.cpp"
#include "REL/mgcpp/assert.cpp"
#include "REL/mgcpp/camera.cpp"
#include "REL/mgcpp/link.cpp"
#include "REL/mgcpp/gameobject.cpp"
#include "REL/mgcpp/minigame.cpp"
#include "REL/mgcpp/model.cpp"
#include "REL/mgcpp/mt19937.cpp"
#include "REL/mgcpp/om.cpp"
#include "REL/mgcpp/random.cpp"
#include "REL/mgcpp/sphere.cpp"
#include "REL/mgcpp/subthread.cpp"
#include "REL/mgcpp/thread.cpp"
#include "REL/mgcpp/timer.cpp"

/* The CMinigameCore singleton pointer: retail's weak template static, at the end of the TU's .bss. */
template <> CMinigameCore* CSingleton<CMinigameCore>::ms_pointer = 0;
