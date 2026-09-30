/* m537.cpp -- the minigame framework unit of m537dll: the shared framework (src/REL/mgcpp) as one
 * translation unit, in retail order. m537's list (plan Phase 4 framework survey): random.cpp and timer.cpp;
 * no handle.cpp, no shadow.cpp, no sphere.cpp. It is the first unit in link order. */
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
#include "REL/mgcpp/subthread.cpp"
#include "REL/mgcpp/thread.cpp"
#include "REL/mgcpp/timer.cpp"

/* The CMinigameCore singleton pointer: retail's weak template static, at the end of the TU's .bss. */
template <> CMinigameCore* CSingleton<CMinigameCore>::ms_pointer = 0;
