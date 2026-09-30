/* m501.cpp -- the minigame framework unit of m501dll. Retail compiled the framework as ONE translation
 * unit made of these files, in this order (the order of .text and of the __FILE__ strings in .data);
 * -inline auto inlines a function only into callers after it, so the order is part of the code. */
#include "REL/mgcpp/new.cpp"
#include "REL/mgcpp/assert.cpp"
#include "REL/mgcpp/camera.cpp"
#include "REL/mgcpp/handle.cpp"
#include "REL/mgcpp/link.cpp"
#include "REL/mgcpp/gameobject.cpp"
#include "REL/mgcpp/minigame.cpp"
#include "REL/mgcpp/model.cpp"
#include "REL/mgcpp/mt19937.cpp"
#include "REL/mgcpp/om.cpp"
#include "REL/mgcpp/sphere.cpp"
#include "REL/mgcpp/subthread.cpp"
#include "REL/mgcpp/thread.cpp"
#include "REL/mgcpp/timer.cpp"

/* The CMinigameCore singleton pointer: retail's weak template static, which lands at the end of the TU's
 * .bss (singleton.h). symbols.txt: instance__13CMinigameCore. */
template <> CMinigameCore* CSingleton<CMinigameCore>::ms_pointer = 0;
