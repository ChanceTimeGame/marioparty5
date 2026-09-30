/* m521.cpp -- the minigame framework unit of m521dll: the shared framework (src/REL/mgcpp) as one
 * translation unit, in retail order. m521's list (plan Phase 4 framework survey, m536's): no handle.cpp; random.cpp
 * between om.cpp and sphere.cpp. It is the THIRD unit in link order (after clock, clockhand). */
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

/* The CMinigameCore singleton pointer is NOT here: retail's weak template static sits in clock.o's .bss (0xC),
 * the first TU in link order that includes minigame.h (clock.cpp defines it). */
